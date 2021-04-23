#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import division  # 精确除法
import cv2  # opencv-python
import numpy as np  # 数学工具

# 计算路径使用 根号0.5
SQRT_0_5 = 0.70710678118654757


class Livewire():
    """
        套索工具类 使用
        1. Canny 边缘检测 + 梯度幅度 + 梯度方向
        2. Dijkstra 算法
    """

    def __init__(self, image):
        self.image = image  #传入的image
        self.x_lim = image.shape[0]  # 高
        self.y_lim = image.shape[1]  # 宽
        # cost矩阵 0-1的范围
        # https://www.cnblogs.com/my-love-is-python/p/10397482.html
        self.cost_edges = 1 - cv2.Canny(image, 85,
                                        170) / 255.0  # Canny opencv 自带 边缘检测
        self.grad_x, self.grad_y, self.grad_mag = self._get_grad(image)  # 使用Sobel运算符返回图像的梯度幅度

        self.cost_grad_mag = 1 - self.grad_mag / np.max(self.grad_mag)  # gard矩阵
        # 权重（Canny边缘，渐变幅度，渐变方向）
        self.weight = (0.425, 0.425, 0.15)

        self.n_pixs = self.x_lim * self.y_lim   # pixs
        self.n_processed = 0    # 进度

    @classmethod
    def _get_grad(cls, image):
        """
        使用Sobel运算符返回图像的梯度幅度
        """
        rgb = True if len(image.shape) > 2 else False
        grad_x = cv2.Sobel(image, cv2.CV_64F, 1, 0, ksize=3)
        grad_y = cv2.Sobel(image, cv2.CV_64F, 0, 1, ksize=3)
        if rgb:
            # 快速验证的近似值
            grad_x = np.max(grad_x, axis=2)
            grad_y = np.max(grad_y, axis=2)

        grad_mag = np.sqrt(grad_x ** 2 + grad_y ** 2)
        grad_x /= grad_mag
        grad_y /= grad_mag

        return grad_x, grad_y, grad_mag

    def _get_neighbors(self, p):
        """
        返回像素p周围的8个邻居
        """
        x, y = p
        x0 = 0 if x == 0 else x - 1
        x1 = self.x_lim if x == self.x_lim - 1 else x + 2
        y0 = 0 if y == 0 else y - 1
        y1 = self.y_lim if y == self.y_lim - 1 else y + 2

        return [(x, y) for x in range(x0, x1) for y in range(y0, y1) if (x, y) != p]

    def _get_grad_direction_cost(self, p, q):
        """
        计算 梯度变化 refer to the link direction
        """
        dp = (self.grad_y[p[0]][p[1]], -self.grad_x[p[0]][p[1]])
        dq = (self.grad_y[q[0]][q[1]], -self.grad_x[q[0]][q[1]])

        l = np.array([q[0] - p[0], q[1] - p[1]], np.float)
        if 0 not in l:
            l *= SQRT_0_5

        dp_l = np.dot(dp, l)
        l_dq = np.dot(l, dq)
        if dp_l < 0:
            dp_l = -dp_l
            l_dq = -l_dq
        # 2/3pi * ...
        return 0.212206590789 * (np.arccos(dp_l) + np.arccos(l_dq))

    def _local_cost(self, p, q):
        """
        1. 欧几里德距离 计算Canny边和梯度幅度成本
        2. 与渐变方向结合
        p q是相邻的
        """
        diagnol = q[0] == p[0] or q[1] == p[1]

        # c0，c1和c2分别是Canny算子，梯度幅度和梯度方向的成本
        if diagnol:
            c0 = self.cost_edges[p[0]][p[1]] - SQRT_0_5 * (self.cost_edges[p[0]][p[1]] - self.cost_edges[q[0]][q[1]])
            c1 = self.cost_grad_mag[p[0]][p[1]] - SQRT_0_5 * (
                    self.cost_grad_mag[p[0]][p[1]] - self.cost_grad_mag[q[0]][q[1]])
            c2 = SQRT_0_5 * self._get_grad_direction_cost(p, q)
        else:
            c0 = self.cost_edges[q[0]][q[1]]
            c1 = self.cost_grad_mag[q[0]][q[1]]
            c2 = self._get_grad_direction_cost(p, q)

        if np.isnan(c2):
            c2 = 0.0

        w0, w1, w2 = self.weight
        cost_pq = w0 * c0 + w1 * c1 + w2 * c2

        return cost_pq * cost_pq

    def get_path_matrix(self, seed):
        """
        从成本矩阵中获取整个图像的路径矩阵
        """
        neighbors = []  # 8 周围的8个点
        processed = set()  # 计算的点
        cost = {seed: 0.0}  # 计算所要的cost，初始化为种子0
        paths = {}  # 路径
        self.n_processed = 0
        while cost:
            # 扩大最低成本点
            p = min(cost, key=cost.get)
            neighbors = self._get_neighbors(p)
            processed.add(p)
            # 记录累积成本和新扩展点的回溯点
            for q in [x for x in neighbors if x not in processed]:
                temp_cost = cost[p] + self._local_cost(p, q)
                if q in cost:
                    if temp_cost < cost[q]:
                        cost.pop(q)
                else:
                    cost[q] = temp_cost
                    processed.add(q)
                    paths[q] = p
            # 弹出遍历的点
            cost.pop(p)
            self.n_processed += 1
        return paths
