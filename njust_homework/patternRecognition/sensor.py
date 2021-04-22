#!/usr/bin/python3
# -*- coding: utf-8 -*-
# @time    : 2021/3/28 13:44
# @author  : lerogo
# @fileName: sensor.py
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
        # 转data list为np array
        for i in self.data_keys:
            tmp_data = self.data.get(i)
            for j in range(len(tmp_data)):
                tmp_data[j].append(1)
                tmp_data[j] = np.array(tmp_data[j])
                if i == self.data_keys[1]:
                    tmp_data[j] = np.multiply(-1, tmp_data[j])

    def start_sensor(self):
        cnt = 0
        print(self.data)
        while cnt < self.max_iteration:
            cnt += 1
            index_num = 0
            for i in self.data_keys:
                tmp_data = self.data.get(i)
                for j in tmp_data:
                    # 对每一个样本进行处理
                    r_num = np.dot(self.args, j)
                    if r_num <= 0.0:
                        print(self.args)
                        print(index_num % 10 + 1, self.args, j, r_num)
                        self.args = np.add(self.args, np.dot(self.rate, j))
                    index_num += 1
        print(self.args)


if __name__ == '__main__':
    fileName = os.getcwd() + "/data/sensor/data.json"
    data = read_data(fileName)
    sensor(data, 1).start_sensor()
