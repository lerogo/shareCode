#!/usr/bin/python3
# -*- coding: utf-8 -*-
# @time    : 2020/10/24 15:42
# @author  : lerogo
# @fileName: main.py


import numpy as np
import pandas as pd
import math
import matplotlib.pyplot as plt

# 解决plt画图中文字体字体
plt.rcParams['font.sans-serif'] = ['Arial Unicode MS']  # macos
# plt.rcParams['font.sans-serif'] = ['KaiTi'] # windows
plt.rcParams['axes.unicode_minus'] = False  # 解决保存图像是负号'-'显示为方块的问题


# 从data读取数据
def readData():
    data_x = pd.read_table("../data/ex4x.dat", sep=' ').values
    x1 = np.array(data_x[:, 3])
    x2 = np.array(data_x[:, 6])
    data_y = pd.read_table("../data/ex4y.dat", sep=' ').values
    y = np.array(data_y[:, 3])
    return x1, x2, y


# 归一化
def normalized(para):
    para = (para - para.min()) / (para.max() - para.min())
    return para


# 反归一化 算出需要的theta
def reverse_normalized_sita(x1: np.ndarray, x2: np.ndarray, ori_sita):
    sita = [0, 0, 0]
    sita[0] = ori_sita[0] - (ori_sita[1] * x1.min()) / (
            x1.max() - x1.min()) - (ori_sita[2] * x2.min()) / (x2.max() - x2.min())
    sita[1] = ori_sita[1] / (x1.max() - x1.min())
    sita[2] = ori_sita[2] / (x2.max() - x2.min())
    return sita


# sita[0] sita[1] 代价函数
def get_cost(x1: np.ndarray, x2: np.ndarray, y: np.ndarray, sita):
    m = len(y)
    hx = h_x(x1, x2, sita)
    cost = -1 / m * ((y * np.log(hx) + (1 - y) * np.log(1 - hx)).sum())
    return cost


def h_x(x1: np.ndarray, x2: np.ndarray, sita):
    hx = []
    for i in range(len(x1)):
        hx.append(1 / (1 + math.exp(-(sita[0] + sita[1] * x1[i] + sita[2] * x2[i]))))
    return np.array(hx)


def get_gradient(x1: np.ndarray, x2: np.ndarray, y: np.ndarray, sita):
    dev = []
    m = len(y)
    hx = h_x(x1, x2, sita)
    dev.append(
        ((1 / m) * (hx - y).sum())
    )
    dev.append(
        ((1 / m) * ((hx - y) * x1).sum())
    )
    dev.append(
        ((1 / m) * ((hx - y) * x2).sum())
    )
    return np.array(dev)


def get_theta(x1, x2, sita, dev):
    H_1 = getH_1(x1, x2, sita)
    sita = np.array(sita)
    tmpSita = [0, 0, 0]
    for i in range(len(dev)):
        tmpSita[i] = sita[i] - np.dot(H_1[i], dev)
    return tmpSita


def getH_1(x1, x2, sita):
    m = len(x1)
    hx = h_x(x1, x2, sita)

    the_matrix = []
    for i in range(m):
        tmp = np.mat([1, x1[i], x2[i]])
        tmp = tmp.T * tmp
        the_matrix.append(tmp)
    the_matrix = np.array(the_matrix)
    H = np.zeros((3, 3))
    for i in range(m):
        H = H + (hx[i] * (1 - hx[i]) * (the_matrix[i]))
    H = H / m
    return np.linalg.pinv(H)


# x,y 步长 sita[0]sita[1] 接受的cost最小多少  最多迭代次数
def gen_ans(x1, x2, y, sita, accept_cost, max_times):
    times = 0  # 迭代次数
    cost = get_cost(x1, x2, y, sita)  # 计算第一次cost
    cost_list = []  # 储存迭代出的cost
    # 开始迭代
    while cost > accept_cost and times < max_times:
        sita = get_theta(
            x1=x1,
            x2=x1,
            sita=sita,
            dev=get_gradient(x1, x2, y, sita),
        )
        cost = get_cost(x1, x2, y, sita)  # 重新计算cost
        cost_list.append(cost)  # 加入cost_list 方便画图
        times += 1
    return sita, cost_list


if __name__ == '__main__':
    data_x1, data_x2, data_y = readData()
    # print(data_x1, data_x2, data_y)
    x1 = normalized(data_x1)
    x2 = normalized(data_x2)
    max_times = 10
    sita, cost_list = gen_ans(
        x1=x1,
        x2=x2,
        y=data_y,
        sita=[0, 0, 0],
        accept_cost=1e-5,
        max_times=max_times,
    )
    print(sita)
    sita = reverse_normalized_sita(data_x1, data_x2, sita)
    print(sita)
    plot_y = -(sita[0] + sita[1] * data_x1) / sita[2]

    # 作出cost的迭代曲线
    plt.title("cost 迭代曲线")
    plt.plot([x for x in range(int(max_times))], cost_list, c='blue', label='cost迭代曲线')
    plt.show()
    # 作出原始值
    plt.title("theta = " + str(np.round(sita, 3)))
    plt.plot(data_x1, plot_y, c='blue', label='决策边界')
    plt.plot(data_x1[:40], data_x2[:40], 'o', c='green', label='Admitted')
    plt.plot(data_x1[40:], data_x2[40:], 'x', c='red', label='Not Admitted')
    plt.plot()
    plt.xlabel('Exam 1 score')
    plt.ylabel('Exam 2 score')
    plt.legend()  # 显示图例
    plt.show()
    exit()
