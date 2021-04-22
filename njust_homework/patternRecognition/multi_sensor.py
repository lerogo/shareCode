#!/usr/bin/python3
# -*- coding: utf-8 -*-
# @time    : 2021/3/28 15:38
# @author  : lerogo
# @fileName: multi_sensor.py

import json
import os
import random

import numpy as np


def read_data(filename: str) -> dict:
    with open(filename, "r", encoding="utf8") as f:
        return json.load(f)


class sensor:

    def __init__(self, data: dict, rate: float = 0.1, max_iteration: int = 1e2):
        # 传入的data
        self.data = data
        # 学习率
        self.rate = rate
        # 最大迭代次数
        self.max_iteration = max_iteration
        # 分的类
        self.data_keys = list(data.keys())
        # 维度
        self.dimension = len(data.get(self.data_keys[0])[0])
        # 有几个维度就有几个参数+1
        self.args = np.array([0 for _ in range(self.dimension + 1)])
        # 判别函数
        self.method = [self.args.copy() for _ in self.data_keys]

        # 转data list为np array
        for i in self.data_keys:
            tmp_data = self.data.get(i)
            for j in range(len(tmp_data)):
                tmp_data[j].append(1)
                tmp_data[j] = np.array(tmp_data[j])

    def start_sensor(self):
        cnt = 0
        while cnt < self.max_iteration:
            cnt += 1
            for i in range(len(self.data_keys)):
                # 该分类下的数据
                tmp_data = self.data.get(self.data_keys[i])
                for j in tmp_data:
                    # 计算每个判别函数的值
                    tmp_num = [np.dot(k, j) for k in self.method]
                    # 查看是否满足条件
                    isChange = False
                    for k in range(len(tmp_num)):
                        # 不满足
                        if k != i and tmp_num[i] <= tmp_num[k]:
                            self.method[k] = np.add(self.method[k], np.dot(-self.rate, j))
                            isChange = True
                    if isChange:
                        self.method[i] = np.add(self.method[i], np.dot(self.rate, j))

        print(self.method)
        self.plotMap()

    def plotMap(self):
        # method_tmp = [self.calMethod(i, (i + 1) % len(self.method)) for i in range(len(self.method))]
        method_tmp = self.method
        import matplotlib.pyplot as plt
        # 解决plt画图中文字体字体
        plt.rcParams['font.sans-serif'] = ['Arial Unicode MS']  # macos
        # plt.rcParams['font.sans-serif'] = ['KaiTi'] # windows
        plt.rcParams['axes.unicode_minus'] = False  # 解决保存图像是负号'-'显示为方块的问题
        plt.plot([-1, 0, 1], [-1, 0, 1], 'o', c='red', label='')
        for tmp_data in method_tmp:
            x_data = [i * 0.01 for i in range(-100, 100)]
            y_data = [-(i * tmp_data[0] + tmp_data[2]) / tmp_data[1] for i in x_data]
            plt.plot(x_data, y_data, '-', c='blue', label='')
        plt.xlabel('X')
        plt.ylabel('Y')
        plt.legend()  # 显示图例
        plt.show()

    def calMethod(self, i, j):
        data_tmp = []
        for ind in range(len(self.method[i])):
            data_tmp.append(self.method[i][ind] - self.method[j][ind])
        return data_tmp


if __name__ == '__main__':
    fileName = os.getcwd() + "/data/sensor/data2.json"
    data = read_data(fileName)
    sensor(data, 1, 200).start_sensor()
