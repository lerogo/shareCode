#!/usr/bin/python3
# -*- coding: utf-8 -*-
# @time    : 2021/3/21 14:38
# @author  : lerogo
# @fileName: __init__.py.py


def plotMap(title, dictionary: dict):
    import matplotlib.pyplot as plt
    # 解决plt画图中文字体字体
    plt.rcParams['font.sans-serif'] = ['Arial Unicode MS']  # macos
    # plt.rcParams['font.sans-serif'] = ['KaiTi'] # windows
    plt.rcParams['axes.unicode_minus'] = False  # 解决保存图像是负号'-'显示为方块的问题
    plt.title(title)
    plt.plot(dictionary.get('x'), dictionary.get('y'), 'o', c='blue', label='数据点')
    plt.plot(dictionary.get('center_x'), dictionary.get('center_y'), 'o', c='red', label='聚类中心')
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.legend()  # 显示图例
    plt.show()
