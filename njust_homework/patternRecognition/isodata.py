#!/usr/bin/python3
# -*- coding: utf-8 -*-
# @time    : 2021/3/21 11:49
# @author  : lerogo
# @fileName: isodata.py
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
        self.dis = 0
        self.gamaNum = []

    def addPoint(self, x, y, i):
        self.pointList.append([x, y, i])

    def clearPoint(self):
        self.pointList.clear()

    def reCalCenterPoint(self):
        self.dis = 0
        xNum = 0
        yNum = 0
        for i in self.pointList:
            xNum += i[0]
            yNum += i[1]
        self.x = xNum / len(self.pointList)
        self.y = yNum / len(self.pointList)

        for i in self.pointList:
            self.dis += math.sqrt((self.x - i[0]) ** 2 + (self.y - i[1]) ** 2)
        self.dis = self.dis / len(self.pointList)

    def calGamaNum(self):
        self.gamaNum = []
        self.gamaNum.append(math.sqrt(sum([(self.x - i[0]) ** 2 for i in self.pointList]) / len(self.pointList)))
        self.gamaNum.append(math.sqrt(sum([(self.y - i[1]) ** 2 for i in self.pointList]) / len(self.pointList)))

    def __str__(self) -> str:
        return "x: " + str(self.x) + "\ty: " + str(self.y) + "\n" + str(self.pointList) + "\n"


class isodata:
    def __init__(self, data, k, sitaN, sitaS, sitaC, l, i):
        self.data = data.copy()
        self.k = k
        self.sitaN = sitaN
        self.sitaS = sitaS
        self.sitaC = sitaC
        self.l = l
        self.i = i
        # self.centerList = [sortClass(data['x'][i], data['y'][i]) for i in range(k)]
        self.centerList = [sortClass(data['x'][0], data['y'][0])]
        self.D_num = 0

    def start_isodata(self):
        iter_num = 0
        while iter_num < self.i:
            iter_num += 1

            [i.clearPoint() for i in self.centerList]

            # 第2步 将N 个模式样本分给最近的类Sj
            for i in range(len(self.data)):
                x = self.data['x'][i]
                y = self.data['y'][i]
                minJ = None
                minNum = None
                for j in range(len(self.centerList)):
                    tmpNum = (x - self.centerList[j].x) ** 2 + (y - self.centerList[j].y) ** 2
                    if minNum is None or minNum > tmpNum:
                        minJ = j
                        minNum = tmpNum
                self.centerList[minJ].addPoint(x, y, i + 1)

            for i in self.centerList:
                print(i)
            plotMap("isodata", {
                "x": self.data['x'],
                "y": self.data['y'],
                "center_x": [i.x for i in self.centerList],
                "center_y": [i.y for i in self.centerList]
            })
            print("\n---------------\n")


            # 第3步
            for sj in self.centerList:
                if len(sj.pointList) < self.sitaN:
                    self.centerList.remove(sj)

            # 第4步 修正聚类中心 第5步各聚类中心间的平均距离
            for sj in self.centerList:
                sj.reCalCenterPoint()

            # 第6步 计算全部模式样本和其对应聚类中心的总平均距离
            D_num = 0
            N_num = 0
            for sj in self.centerList:
                N_num += len(sj.pointList)
                D_num += sj.dis * len(sj.pointList)
            D_num = D_num / N_num
            self.D_num = D_num

            # 第7步：判别分裂、合并及迭代运算
            if iter_num == self.i:
                self.sitaC = 0
                self.mergeClass()
            elif (len(self.centerList) << 1) <= self.k:
                self.divideClass()
            elif iter_num % 2 == 0 or len(self.centerList) >= self.k << 1:
                self.mergeClass()
            else:
                self.divideClass()

    def divideClass(self):
        for i in self.centerList:
            i.calGamaNum()
            gamaMaxNum = max(i.gamaNum)
            if gamaMaxNum > self.sitaS and ((i.dis > self.D_num and len(i.pointList) > (self.sitaN + 1) << 1) or len(
                    self.centerList) << 1 <= self.k):
                if i.gamaNum[0] == gamaMaxNum:
                    self.centerList.append(sortClass(i.x + 0.5 * gamaMaxNum, i.y))
                    self.centerList.append(sortClass(i.x - 0.5 * gamaMaxNum, i.y))
                else:
                    self.centerList.append(sortClass(i.x, i.y + 0.5 * gamaMaxNum))
                    self.centerList.append(sortClass(i.x, i.y - 0.5 * gamaMaxNum))
                self.centerList.remove(i)
                break

    def mergeClass(self):
        tmp_d_list = [[1e10 for i in self.centerList] for j in self.centerList]
        cal_list = []
        for i in range(len(self.centerList)):
            for j in range(i):
                tmpNum = math.sqrt((self.centerList[i].x - self.centerList[j].x) ** 2 + (
                        self.centerList[i].y - self.centerList[j].y) ** 2)
                tmp_d_list[i][j] = tmpNum
                if tmpNum < self.sitaC:
                    cal_list.append([i, j])
        while len(cal_list) > 0:
            minInd = None
            minNum = None
            for i in cal_list:
                tmpNum = tmp_d_list[i[0]][i[1]]
                if minNum is None or minNum > tmpNum:
                    minInd = i
                    minNum = tmpNum
            iClass = self.centerList[minInd[0]]
            jClass = self.centerList[minInd[1]]
            xInd = (iClass.x * len(iClass.pointList) + jClass.x * len(jClass.pointList)) / (len(iClass.pointList) + len(
                jClass.pointList))
            yInd = (iClass.y * len(iClass.pointList) + jClass.y * len(jClass.pointList)) / (len(iClass.pointList) + len(
                jClass.pointList))
            self.centerList.append(sortClass(xInd, yInd))
            cal_list.remove(minInd)
            self.centerList.remove(iClass)
            self.centerList.remove(jClass)
            for i in range(len(tmp_d_list)):
                tmp_d_list[i][minInd[1]] = 1e10
                tmp_d_list[minInd[0]][i] = 1e10


if __name__ == '__main__':
    fileName = os.getcwd() + "/data/isodata/data.csv"
    r = readCsv(fileName)
    isodata(r, 3, 1, 1, 4, 1, 5).start_isodata()



