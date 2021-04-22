#!/usr/bin/python3
# -*- coding: utf-8 -*-
# @time    : 2021/4/7 17:36
# @author  : lerogo
# @fileName: pca.py
import os
from PIL import Image
import numpy as np


# 定义PCA算法
def PCA(img_arr):
    # 人脸均值 压缩行
    face_avg = np.mean(img_arr, axis=0)
    # 中心化
    img_arr = np.subtract(img_arr, face_avg)
    # 计算协方差
    face_cov = np.cov(img_arr, rowvar=False)
    # 计算特征值和特征向量
    c, d = np.linalg.eig(face_cov)
    print(c,d)
    d1 = np.multiply(c, d)
    c_tmp_sum = c_sum = c.sum()
    c_num = 0
    # 选取90%的特征
    while c_tmp_sum / c_sum > 0.1:
        c_tmp_sum -= c[c_num]
        c_num += 1
    d = d[:, :c_num]
    # 特征脸
    # for i in range(c_num):
    #     Image.fromarray(d1.T[i].reshape(row, col)).show()
    return d


if __name__ == '__main__':
    # 图片文件目录地址
    file_path = os.path.join(os.getcwd(), "data/pca/AR_Gray_50by40/")
    # 获取每个图片地址
    img_path_list = [os.path.join(file_path, i) for i in os.listdir(file_path)]
    # 读取每一张图片 并转为1维
    img_list = [np.array(Image.open(i)) for i in img_path_list]
    # 获取每张图片的行列
    row, col = img_list[0].shape
    img_list = [i.flatten() for i in img_list]
    # 转为np arr
    img_arr = np.array(img_list)
    d = PCA(img_arr.copy())
    for i in range(10):
        input('Press Enter')
        # 原始图像
        Image.fromarray(img_arr[i].reshape(row, col)).show()

        input('Press Enter')
        # 使用降维后复原
        Image.fromarray(np.matmul(d, np.matmul(d.T, img_arr[i])).reshape(row, col)).show()
