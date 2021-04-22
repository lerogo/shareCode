#!/usr/bin/python3
# -*- coding: utf-8 -*-
# @time    : 2021/3/28 18:38
# @author  : lerogo
# @fileName: Normality.py
import json
import math
import os

import numpy as np


def read_data(filename: str) -> dict:
    with open(filename, "r", encoding="utf8") as f:
        return json.load(f)


class normality:
    """
    两类正态分布
    """

    def __init__(self, data, pw: list):
        # 传入的data
        self.data = data
        # 传入的先验概率
        self.pw = pw
        # 分的类
        self.data_keys = list(data.keys())
        # 数据 维度
        self.dimension = len(data.get(self.data_keys[0])[0])
        # 均值向量
        self.mean_vec = self.get_mean_vec()
        # 协方差矩阵
        self.covariance = self.get_covariance()

        self.result = self.start_normality()

        print(self.result)

        self.plotMap()

    def start_normality(self):
        # 逆矩阵
        covariance_inv = [np.linalg.inv(self.covariance[i]) for i in range(len(self.covariance))]
        # 行列式
        covariance_det = [np.linalg.det(self.covariance[i]) for i in range(len(self.covariance))]

        dix = []
        for i in range(len(self.data_keys)):
            tmp_data_num = [0, 0, 0, 0, 0, 0]
            tmp_num = math.log(self.pw[i]) - (1 / 2) * math.log(math.fabs(covariance_det[i]))
            a = covariance_inv[i][0, 0]
            b = covariance_inv[i][0, 1]
            c = covariance_inv[i][1, 0]
            d = covariance_inv[i][1, 1]
            m1 = self.mean_vec[i][0]
            m2 = self.mean_vec[i][1]
            tmp_data_num[0] = a
            tmp_data_num[1] = d
            tmp_data_num[2] = c + b
            tmp_data_num[3] = 2 * a * m1 - c * m2 - b * m2
            tmp_data_num[4] = 2 * d * m2 - c * m1 - b * m1
            tmp_data_num[5] = -(a * (m1 ** 2) + ((c + b) * m1 * m2) + d * (m2 ** 2))
            tmp_data_num = np.divide(np.array(tmp_data_num), 2)
            tmp_data_num[5] += tmp_num
            dix.append(tmp_data_num)
        return np.subtract(dix[0], dix[1])

    def get_mean_vec(self):
        """
        :return: 均值向量
        """
        mean_vec = [[] for _ in range(len(self.data_keys))]
        for i in range(len(self.data_keys)):
            tmp_data = np.array(self.data.get(self.data_keys[i]))
            for j in range(self.dimension):
                mean_vec[i].append(np.average(tmp_data[:, j]))
        return np.array(mean_vec)

    def get_covariance(self):
        """
        :return: 协方差矩阵
        """
        covariance_data = [0 for _ in range(len(self.data_keys))]
        tmp_covariance_data = [0 for _ in range(len(self.data_keys))]
        for i in range(len(self.data_keys)):
            tmp_data = np.array(self.data.get(self.data_keys[i]))
            tmp_covariance_data[i] = np.subtract(tmp_data, self.mean_vec[i])

        for ind in range(len(tmp_covariance_data)):
            tmp_array = np.zeros((self.dimension, self.dimension))
            for i in range(self.dimension):
                for j in range(i + 1):
                    tmp_array[i, j] = np.dot(tmp_covariance_data[ind][:, i],
                                             tmp_covariance_data[ind][:, j]) / len(tmp_covariance_data[ind][:, i])
                    tmp_array[j, i] = tmp_array[i, j]
            covariance_data[ind] = tmp_array.copy()
        return covariance_data

    def plotMap(self):
        import matplotlib.pyplot as plt
        # 解决plt画图中文字体字体
        plt.rcParams['font.sans-serif'] = ['Arial Unicode MS']  # macos
        # plt.rcParams['font.sans-serif'] = ['KaiTi'] # windows
        plt.rcParams['axes.unicode_minus'] = False  # 解决保存图像是负号'-'显示为方块的问题
        plt.plot([0, 2, 2, 0], [0, 0, 2, 2], 'o', c='red', label='')
        plt.plot([4, 6, 6, 4], [4, 4, 6, 6], 'o', c='blue', label='')
        x_data = [i * 0.01 for i in range(-100, 1000)]
        y_data = [-(i * self.result[3] + self.result[5]) / self.result[4] for i in x_data]
        plt.plot(x_data, y_data, '-', c='green', label='')
        plt.xlabel('X')
        plt.ylabel('Y')
        plt.legend()  # 显示图例
        plt.show()


if __name__ == '__main__':
    fileName = os.getcwd() + "/data/normality/data.json"
    data = read_data(fileName)
    normality(data, [1 / 2, 1 / 2]).start_normality()
