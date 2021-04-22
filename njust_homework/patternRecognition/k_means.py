#!/usr/bin/python3
# -*- coding: utf-8 -*-
# @time    : 2021/3/16 15:43
# @author  : lerogo
# @fileName: k_means.py.py
import math
import os
import pandas as pd

from patternRecognition.utils import plotMap


def readCsv(filename: str) -> list:
    """读取csv"""
    with open(filename, "r", encoding="utf8") as f:
        return pd.read_csv(f)


class sortClass:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.pointList = []

    def addPoint(self, x, y, i):
        self.pointList.append([x, y, i])

    def clearPoint(self):
        self.pointList.clear()

    def reCalCenterPoint(self):
        xNum = 0
        yNum = 0
        for i in self.pointList:
            xNum += i[0]
            yNum += i[1]
        self.x = xNum / len(self.pointList)
        self.y = yNum / len(self.pointList)

    def __str__(self) -> str:
        return "x: " + str(self.x) + "\ty: " + str(self.y) + "\n" + str(self.pointList) + "\n"


class kMeans:
    def __init__(self, data, k: int):
        self.data = data
        self.k = k
        self.centerList = [sortClass(data['x'][i], data['y'][i]) for i in range(k)]
        # self.centerList = [sortClass(data['x'][0], data['y'][0]), sortClass(data['x'][9], data['y'][9])]

    def start_k_means(self):
        lastValue = None
        thisValue = None
        cnt = 100
        while lastValue is None or (lastValue - thisValue > 1e-3 and cnt > 0):
            [i.clearPoint() for i in self.centerList]
            data = {
                "x": r['x'],
                "y": r['y'],
                "center_x": [i.x for i in k_means_obj.centerList],
                "center_y": [i.y for i in k_means_obj.centerList]
            }
            plotMap("k-means", data)

            cnt -= 1
            lastValue = thisValue
            thisValue = 0
            for i in range(len(self.data)):
                x = self.data['x'][i]
                y = self.data['y'][i]
                minJ = None
                minNum = None
                for j in range(self.k):
                    tmpNum = math.sqrt((x - self.centerList[j].x) ** 2 + (y - self.centerList[j].y) ** 2)
                    if minNum is None or minNum > tmpNum:
                        minJ = j
                        minNum = tmpNum
                self.centerList[minJ].addPoint(x, y, i + 1)
                thisValue += minNum
            # thisValue = math.sqrt(thisValue)
            for i in range(self.k):
                print(self.centerList[i])
                self.centerList[i].reCalCenterPoint()

            print(thisValue, "\n", "---------------\n")


if __name__ == '__main__':
    fileName = os.getcwd() + "/data/k_means/data.csv"
    r = readCsv(fileName)
    k = 2
    k_means_obj = kMeans(r, k)
    k_means_obj.start_k_means()
