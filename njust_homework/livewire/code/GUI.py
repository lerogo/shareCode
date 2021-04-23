#!/usr/bin/env python
# -*- coding: utf-8 -*-
import os
from threading import Thread
from tkinter import *
import tkinter as tk
from tkinter import filedialog

import cv2
from PIL import Image, ImageTk
import time

from livewire import Livewire

LOG_LINE_NUM = 0


class MY_GUI():
    # 创建一个窗口
    def __init__(self, init_window):
        self.tk = tk  # 调用tk方法使用
        self.mainWindow = init_window  # 初始化父窗口
        self.mainWindow.title("智能剪刀 - by 黄海浪 9181040G0818")  # 窗口名
        self.mainWindow.geometry('1367x800+280+90')  # 1367x800为窗口大小，+280+90 定义窗口弹出时的默认展示位置
        self.mainWindow.resizable(0, 0)  # 窗口不可调节大小

        self.imageFilePath = None  # 初始化图片地址
        self.cv2_image = None  # 原始读入图片     进行处理的图片
        self.pil_image = None  # 初始化调整后的显示图片 tk必须使用pil类型的
        self.lw = None  # 算法处理  # liveWire的算法类
        self.seed = None  # 点（之前的点） 种子
        self.path_map = {}  # 存放所有路径    计算的路径
        self.path = []  # 存放点击之前的路径  保存图片需要
        self.active = False  # 是否允许实时计算 计算有结果后为 True
        self.seed_enabled = True  # 是否允许点一个点    刚开始允许计算点
        self.finish_enable = False
        self.allOvals = []  # 画的点 用来重新计算时进行清除   move时清除的临时点

        # 注册一个按钮 （打开图片）
        self.openImageButton = Button(self.mainWindow, text="打开图片", bg="lightblue", width=8, height=2,
                                      command=self.loadPic)  # 调用内部方法  加()为直接调用
        self.openImageButton.grid(row=0, column=0, sticky=W)

        # 注册一个按钮 （保存图片）
        self.openImageButton = Button(self.mainWindow, text="保存图片", bg="lightblue", width=8, height=2,
                                      command=self.savePic)  # 调用内部方法  加()为直接调用
        self.openImageButton.grid(row=0, column=20, sticky=E)

        # 初始化提示（请打开图片）
        self.mainWindow.label = tk.Label(self.mainWindow, text="请点击打开图片", width=133, height=2)
        self.mainWindow.label.grid(row=20, column=1)

        # 提示操作
        self.mainWindow.label2 = tk.Label(self.mainWindow, text="鼠标左单击：新的一个点 / 右击: 结束", width=133, height=2)
        self.mainWindow.label2.grid(row=40, column=1)

        # 创建Canvas  显示图片和绘图
        self.mainWindow.canvas = tk.Canvas(self.mainWindow, width=1367 / 1.2, height=800 / 1.15)

    def clickEvent(self, event):
        h, w = self.cv2_image.shape[0], self.cv2_image.shape[1]
        if event.x >= w or event.y >= h:
            return
        print("当前位置：", event.x, event.y)
        if self.seed_enabled:
            p = event.y, event.x  # 获取当前点
            seed = self.seed  # 获取上一个点
            self.seed = p  # 刷新上一个点
            if self.active and self.path_map:  # 将路径压入 self.path
                while p != seed:  # 将选择的路径压入path中
                    p = self.path_map[p]
                    self.path.append(p)
                    # 画出已经选择的点（目前）
                    self.mainWindow.canvas.create_oval(p[1]-1, p[0]-1, p[1]-1, p[0]-1, fill="#33FF00")
            # 重新计算
            Thread(target=self._cal_path_matrix).start()
            Thread(target=self._update_path_map_progress).start()

    def motionEvent(self, event):
        if self.active:
            x, y = event.x, event.y
            p = y, x
            # 清空之前画的点
            for i in self.allOvals:
                self.mainWindow.canvas.delete(i)
            self.allOvals = []

            while p != self.seed:
                try:
                    p = self.path_map[p]
                except KeyError:
                    continue
                # 画出刚运算的点
                qq = self.mainWindow.canvas.create_oval(p[1]-1, p[0]-1, p[1]-1, p[0]-1, fill="#33FF00")
                self.allOvals.append(qq)

    def clickClearEvent(self, event):
        h, w = self.cv2_image.shape[0], self.cv2_image.shape[1]
        if event.x >= w or event.y >= h:
            return
        print("当前位置：", event.x, event.y)
        if self.active:
            self.active = False
            p = event.y, event.x  # 获取当前点
            seed = self.seed  # 获取上一个点
            if self.path_map:  # 将路径压入 self.path
                while p != seed:  # 将选择的路径压入path中
                    p = self.path_map[p]
                    self.path.append(p)
                    # 画出已经选择的点（目前）
                    self.mainWindow.canvas.create_oval(p[1]-1, p[0]-1, p[1]-1, p[0]-1, fill="#33FF00")

    def loadPic(self):
        self.imageFilePath = self.getFile()
        if self.imageFilePath is None or len(self.imageFilePath) == 0:
            return
        # cv2读取不失真
        self.cv2_image = self.cv2Resize(1367 / 1.2, 800 / 1.15, cv2.imread(self.imageFilePath))
        # self.export_image = self.cv2_image
        self.lw = Livewire(self.cv2_image)
        # 转换为pil_image
        self.pil_image = Image.fromarray(cv2.cvtColor(self.cv2_image, cv2.COLOR_BGR2RGB))
        self.mainWindow.tkImage = ImageTk.PhotoImage(self.pil_image)
        self.updateCanvas()

    def updateCanvas(self):
        cc = self.mainWindow.canvas.create_image(0, 0, anchor=NW, image=self.mainWindow.tkImage)
        # 监听鼠标
        self.mainWindow.canvas.tag_bind(cc, "<Motion>", self.motionEvent)
        self.mainWindow.canvas.bind("<Button-1>", self.clickEvent)
        self.mainWindow.canvas.bind("<Button-3>", self.clickClearEvent)
        # 格式化窗口
        self.mainWindow.canvas.grid(row=20, column=1)

    def savePic(self):
        self.imageFilePath = self.saveFile()
        if self.imageFilePath is None or len(self.imageFilePath) == 0:
            return
        image = self.cv2_image.copy()
        # 画出之前的点
        if self.path:
            for p in self.path:
                cv2.circle(image, (p[1], p[0]), 1, (255, 0, 0), thickness=-1)
        cv2.imwrite(self.imageFilePath, image)

    # 打开一个框 获取拿到的文件名
    def getFile(self):
        fileName = tk.filedialog.askopenfilename(title=u'选择文件', initialdir=(os.path.expanduser("./")),
                                                 filetypes=[("PIC", ".png"), ("PIC", ".jpg"), ("PIC", ".jepg")])
        return fileName

    # 打开一个框 获取拿到的文件名
    def saveFile(self):
        fileName = tk.filedialog.asksaveasfilename(title=u'保存文件', initialdir=(os.path.expanduser("./")),
                                                   filetypes=[("png", ".png"), ("jpg", ".jpg"), ("jepg", ".jepg")])
        return fileName

    # cv2 image 格式化大小适应窗口
    def cv2Resize(self, w_box, h_box, cv2_image):
        h, w = cv2_image.shape[0], cv2_image.shape[1]
        f1 = 1.0 * w_box / w  # 1.0 forces float division in Python2
        f2 = 1.0 * h_box / h
        factor = min([f1, f2])
        width = int(w * factor)
        height = int(h * factor)
        return cv2.resize(cv2_image, (width, height), interpolation=cv2.INTER_CUBIC)

    def _cal_path_matrix(self):
        self.seed_enabled = False
        self.active = False
        self.mainWindow.label2 = tk.Label(self.mainWindow, text="开始计算所有点到种子点路径...", width=133, height=2)
        self.mainWindow.label2.grid(row=40, column=1)
        path_matrix = self.lw.get_path_matrix(self.seed)  # 计算得到每一个点的路径
        self.mainWindow.label2 = tk.Label(self.mainWindow, text="鼠标左单击：新的一个点 / 右击: 结束", width=133, height=2)
        self.mainWindow.label2.grid(row=40, column=1)
        self.seed_enabled = True
        self.active = True

        self.path_map = path_matrix

    def _update_path_map_progress(self):
        # 多线程刷新
        while not self.seed_enabled:
            time.sleep(0.1)
            self.mainWindow.label2 = tk.Label(self.mainWindow, text="正在计算中..." + str(round(
                self.lw.n_processed / self.lw.n_pixs * 100.0, 2)) + "%", width=133, height=2)
            self.mainWindow.label2.grid(row=40, column=1)
        self.mainWindow.label2 = tk.Label(self.mainWindow, text="鼠标左单击：新的一个点 / 右击: 结束", width=133, height=2)
        self.mainWindow.label2.grid(row=40, column=1)


def gui_start():
    init_window = Tk()  # 实例化出一个父窗口
    ZMJ_PORTAL = MY_GUI(init_window)
    init_window.mainloop()  # 父窗口进入事件循环，可以理解为保持窗口运行，否则界面不展示
