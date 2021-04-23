#!/usr/bin/python3
# -*- coding: utf-8 -*-
# @time    : 2020/11/14 19:56
# @author  : lerogo
# @fileName: main.py

# 导入包
from libsvm.svm import *
from libsvm.svmutil import *
import numpy as np
import pandas as pd


# 从data读取数据
def readData():
    data_x = pd.read_table("./data/ex4x.dat", sep=' ').values
    data_y = pd.read_table("./data/ex4y.dat", sep=' ').values
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


if __name__ == "__main__":
    dataX, dataY = readData()  # 初始化训练数据
    # 归一化
    dataX[:, 1] = normalized(dataX[:, 1])
    dataX[:, 2] = normalized(dataX[:, 2])

    # 输入数据
    problem = svm_problem(dataY, dataX, isKernel=True)
    # 采用多项式核函数-t 1,5倍交叉验证模式-v 5
    options = svm_parameter('-s 0 -t 1 -v 5')
    # 训练
    model = svm_train(problem, options)

