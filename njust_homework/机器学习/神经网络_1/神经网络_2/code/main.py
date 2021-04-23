#!/usr/bin/python3
# -*- coding: utf-8 -*-
# @time    : 2020/11/1 18:41
# @author  : lerogo
# @fileName: main.py
import json
import random

# from pandas import np
from sklearn.model_selection import KFold
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
    dataX = np.array([x0, x1, x2]).T
    dataY = np.array(y).T
    trainIndex = []
    testIndex = []
    for train_index, test_index in KFold(n_splits=5, shuffle=True).split(X=dataX):
        trainIndex.append(train_index)
        testIndex.append(test_index)
    return dataX, dataY, trainIndex, testIndex


# 归一化
def normalized(para):
    para = (para - para.min()) / (para.max() - para.min())
    return para


def sigmoid(x):
    return 1.0 / (1 + math.exp(-x))


def calNNY(x, vh, wh, gamaH, thetaJ):
    bh = calBh(x, vh, gamaH)
    beita = np.dot(bh, wh)
    # y = list()
    # for i in range(len(beita)):
    #     y.append(sigmoid(beita[i] + thetaJ))
    # y = np.array(y)
    y = sigmoid(beita[0] + thetaJ)
    return y


# def calNpArrY(dataX, vh, wh, gamaH, thetaJ):
#     y = list()
#     for i in range(len(dataX)):
#         y.append(calNNY(dataX[i], vh, wh, gamaH, thetaJ))
#     y = np.array(y)
#     return y


def calCost(y, dataYi):
    # y = calNpArrY(dataX, vh, wh, gamaH, thetaJ)
    return math.pow(y - dataYi, 2) / 2


def calDertaGd(x, y, dataYi, vh, wh, gamaH, thetaJ, yita):
    gi = calGi(y, dataYi)
    bh = calBh(x, vh, gamaH)
    eh = calEh(wh, gi, bh)

    dertaWh = yita * gi * bh
    dertaThetaj = -yita * gi
    dertaVih = yita * np.dot(np.array([x]).T, np.array([eh]))
    dertaGameH = -yita * eh
    return np.array([dertaWh]).T, dertaThetaj, dertaVih, np.array([dertaGameH])


def calGi(y, dataYi):
    gi = y * (1 - y) * (dataYi - y)
    return gi


def calBh(x, vh, gamaH):
    ah = np.dot(x, vh)
    bh = list()
    for i in range(len(ah)):
        bh.append(sigmoid(ah[i] + gamaH[0, i]))
    return np.array(bh)


def calEh(wh, gi, bh):
    eh = bh * (1 - bh) * (wh[:, 0] * gi).T
    return eh


def gen_ans(dataX, dataY, maxTimes):
    costList = list()
    dataSamples, dataFeatures = dataX.shape  # 63 3
    yita = 0.01  # 学习率
    hiddenLayerNum = 4  # 第二层数量
    thetaJ = random.random()  # theta J
    # gamaH = np.zeros((1, hiddenLayerNum))
    gamaH = np.random.rand(1, hiddenLayerNum)
    # vh = np.zeros((dataFeatures, hiddenLayerNum))
    vh = np.random.rand(dataFeatures, hiddenLayerNum)
    # wh = np.zeros((hiddenLayerNum, 1))
    wh = np.random.rand(hiddenLayerNum, 1)
    for time in range(maxTimes):
        coooost = 0
        for i in range(len((dataX))):
            y = calNNY(dataX[i], vh, wh, gamaH, thetaJ)
            cost = calCost(y, dataY[i])
            coooost += cost
            dertaWh, dertaThetaj, dertaVih, dertaGameH = calDertaGd(dataX[i], y, dataY[i], vh, wh, gamaH, thetaJ, yita)
            wh = wh + dertaWh
            thetaJ = thetaJ + dertaThetaj
            vh = vh + dertaVih
            gamaH = gamaH + dertaGameH
            # print(wh, thetaJ, vh, gamaH)
        costList.append(coooost)

    return costList, wh, thetaJ, vh, gamaH


def predictCost(testDataX, testDataY, wh, thetaJ, vh, gamaH):
    accuracy = 0
    for index in range(len(testDataX)):
        pry = calNNY(testDataX[index], vh, wh, gamaH, thetaJ)
        # if pry >= 0.5:
        #     pry = 1
        # else:
        #     pry = 0
        print(testDataY[index], pry)
        accuracy += math.pow(testDataY[index] - pry, 2)
    return accuracy


if __name__ == '__main__':
    dataX, dataY, trainIndex, testIndex = readData()  # 初始化训练数据
    oriDataX = dataX.copy()
    oriDataY = dataY.copy()
    dataX[:, 1] = normalized(dataX[:, 1])
    dataX[:, 2] = normalized(dataX[:, 2])
    # print(dataX)

    maxTimes = int(1e4)
    dataList = list()
    for i in range(len(trainIndex)):
        costList, wh, thetaJ, vh, gamaH = gen_ans(
            dataX[trainIndex[i]], dataY[trainIndex[i]], maxTimes
        )
        plt.title("cost 迭代曲线")
        plt.plot([x for x in range(len(costList))], costList, c='blue', label='cost迭代曲线')
        plt.show()

        testDataX = dataX[testIndex[i]]
        testDataY = dataY[testIndex[i]]
        accuracy = predictCost(testDataX, testDataY, wh, thetaJ, vh, gamaH)
        print(accuracy)
        dataList.append({
            "costList": costList, "wh": str(wh), "thetaJ": str(thetaJ), "vh": str(vh), "gamaH": str(gamaH),
            "accuracy": str(accuracy)
        })
    # print(dataList)
    with open("dataList.json", "w") as f:
        json.dump(dataList, f)
    # 作出cost的迭代曲线
#     plotX2 = (-thetas[1, 0] - thetas[1, 1] * oriDataX[:, 1]) / thetas[1, 2]
#     # 作出原始值
#     plt.title("theta = " + str(np.round(thetas, 3)))
#     plt.plot(oriDataX[:, 1], plotX2, c='blue', label='决策边界')
#     plt.plot(oriDataX[:40, 1], oriDataX[:40, 2], 'o', c='green', label='Admitted')
#     plt.plot(oriDataX[40:, 1], oriDataX[40:, 2], 'x', c='red', label='Not Admitted')
#     plt.plot()
#     plt.xlabel('Exam 1 score')
#     plt.ylabel('Exam 2 score')
#     plt.legend()  # 显示图例
#     plt.show()
#     exit()
