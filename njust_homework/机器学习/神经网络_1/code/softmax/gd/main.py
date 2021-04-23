#!/usr/bin/python3
# -*- coding: utf-8 -*-
# @time    : 2020/10/24 13:21
# @author  : lerogo
# @fileName: main.py

import csv

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
    data_y = pd.read_table("../data/ex4y.dat", sep=' ').values
    x1 = []
    x2 = []
    x0 = []
    y = []
    for i in range(len(data_y[:, 3])):
        x0.append(1.0)
        x1.append(float(data_x[:, 3][i]))
        x2.append(float(data_x[:, 6][i]))
        y.append(int(data_y[:, 3][i]))
    dataX = np.array([x0, x1, x2])
    dataY = np.array(y)
    return dataX.T, dataY.T


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


def gen_ans(dataX, dataY, ALPHA, LAMBDA, acceptCost, maxTimes):
    classNum = len(set(dataY))  # 分类数量
    costList = list()
    # 共dataSamples个训练数据、x维度为dataFeatures
    dataSamples, dataFeatures = dataX.shape
    # thetas = np.random.rand(classNum, dataFeatures)  # 随机初始化权重矩阵 算出来和梯度不一样
    thetas = np.zeros((classNum, dataFeatures))  # 随机初始化权重矩阵
    classYHot = np.zeros((dataSamples, classNum))
    classYHot[np.arange(dataSamples), dataY.T] = 1  # 分类器 在矩阵中 为1的表示y为那一类
    for i in range(maxTimes):
        # 计算 X*thetas 的矩阵  得到一个 m*classNum 的矩阵
        thetaMulX = np.dot(dataX, thetas.T)
        # 计算 求和
        sumThetaMulX = np.sum(np.exp(thetaMulX), axis=1, keepdims=True)
        # 得到hx
        hThetaX = np.exp(thetaMulX) / sumThetaMulX
        # 计算cost
        cost = - (1.0 / dataSamples) * np.sum(classYHot * np.log(hThetaX))
        costList.append(cost)
        # 计算梯度
        gradient = -(1.0 / dataSamples) * np.dot((classYHot - hThetaX).T, dataX) + LAMBDA * thetas
        gradient[:, 0] = gradient[:, 0] - LAMBDA * thetas[:, 0]
        # 更新参数
        thetas = thetas - ALPHA * gradient
    return thetas, costList


if __name__ == '__main__':
    dataX, dataY = readData()  # 初始化训练数据
    oriDataX = dataX.copy()
    dataX[:, 1] = normalized(dataX[:, 1])
    dataX[:, 2] = normalized(dataX[:, 2])

    ALPHA = 0.01  # 学习率
    LAMBDA = 0  # 正则
    acceptCost = float(1e-5)
    maxTimes = int(1e5)
    thetas, costList = gen_ans(
        dataX, dataY, ALPHA, LAMBDA, acceptCost, maxTimes
    )
    print(thetas)
    thetas[0] = reverse_normalized_sita(oriDataX[:, 1], oriDataX[:, 2], thetas[0])
    thetas[1] = reverse_normalized_sita(oriDataX[:, 1], oriDataX[:, 2], thetas[1])
    print("cost", costList[-1])
    # 作出cost的迭代曲线
    plt.title("cost 迭代曲线")
    plt.plot([x for x in range(len(costList))], costList, c='blue', label='cost迭代曲线')
    plt.show()
    plotX2 = (-thetas[1, 0] - thetas[1, 1] * oriDataX[:, 1]) / thetas[1, 2]
    # 作出原始值
    plt.title("theta = " + str(np.round(thetas, 3)))
    plt.plot(oriDataX[:, 1], plotX2, c='blue', label='决策边界')
    plt.plot(oriDataX[:40, 1], oriDataX[:40, 2], 'o', c='green', label='Admitted')
    plt.plot(oriDataX[40:, 1], oriDataX[40:, 2], 'x', c='red', label='Not Admitted')
    plt.plot()
    plt.xlabel('Exam 1 score')
    plt.ylabel('Exam 2 score')
    plt.legend()  # 显示图例
    plt.show()
    exit()
