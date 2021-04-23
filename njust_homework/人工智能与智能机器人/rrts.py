#!/usr/bin/python3
# -*- coding: utf-8 -*-
# @time    : 2020/12/21 23:17
# @author  : lerogo
# @fileName: rrts.py
# !/usr/bin/env python3
# coding:utf-8
"""
RRT RRT* RRT-connect
"""

import math
import random

import numpy as np
import numpy.linalg as lng


class RRT:
    def __init__(self, _map, method, initInfo: dict):
        self.map = _map  # 地图
        self.method = method  # 方法
        self.trees = []  # 树
        self.nInit = Node(self.map.pInit, cost=0, lcost=0)  # 起点 cost为0
        self.nGoal = Node(self.map.pGoal)  # 目标点
        self.prob = 0.1  # 以一定概率偏向 终点
        self.stepSize = 1  # 向前 增长多少
        self.canACC = initInfo.get('goalRadius')  # 多少ACC
        self.DISCRETE = 0.05  # 冲突
        self.path = []  # 路径
        self.pathCost = float('inf')  # 路径花费
        self.initInfo = initInfo  # 初始化信息
        self.success = False  # 是否已经找到
        self.path_x = []  # 画图
        self.path_y = []  # 画图

    def Search(self):
        if self.method == "RRT":
            self.rrtSearch()
        elif self.method == "RRT-Connect":
            self.prob = 0
            self.rrtConnectSearch()
        elif self.method == "RRT*":
            self.rrtStarSearch()

    def getPath(self):
        # 不可能超过3颗树
        t = self.trees[0]
        n = t.nodes[-1]
        sum = 0
        while n.parent:
            self.path.append(n.x)
            n = n.parent
            sum += n.lcost
        self.path.append(n.x)
        if len(self.trees) > 1:
            nl = n
            n = self.trees[2].root
            sum += Node.distance(nl, n)
            while n.parent:
                self.path.insert(0, n.parent.x)
                n = n.parent
                sum += n.lcost

        self.pathCost = sum
        for val in self.path:
            self.path_x.append(val[0])
            self.path_y.append(val[1])

    def rrtSearch(self):
        if len(self.trees) == 0:
            tree = Tree(self.nInit)  # 以初始点作为树
            self.trees.append(tree)  # 树 增加节点（rrt只有一棵树）
        else:
            tree = self.trees[0]
        if self.success:
            self.initInfo.get('newNode')[1].label = '► 开始'
            try:
                from bokeh.io import curdoc
                curdoc().remove_periodic_callback(self.initInfo.get('callback_id'))
            except Exception:
                pass
            return True
        xrand = self.SampleRandomFreeFast()  # 随机一个点
        # self.initInfo.get('p').circle(x=xrand[0], y=xrand[1], size=1, color='red', alpha=1)
        nnearest, dis = tree.getNearest(xrand)  # 拿到一个树中 最近的一个点
        nnew = self.Extend(nnearest, xrand)  # 增长 一个点
        if nnew is not None:  # 没有碰撞
            tree.addNode(nnew)  # 树中增加 点
            self.initInfo.get('p').rect(x=nnew.x[0], y=nnew.x[1], width=0.6, height=0.6, color='blue', alpha=1,
                                        line_color=None)
            if Node.distance(nnew, self.nGoal) < self.canACC:  # 如果找到
                tree.addNode(self.nGoal, parent=nnew)
                self.success = True
                self.getPath()
                self.initInfo.get('p').line(self.path_x, self.path_y, line_width=3, color='red')
                self.initInfo.get('newNode')[1].label = '► 开始'
                try:
                    from bokeh.io import curdoc
                    curdoc().remove_periodic_callback(self.initInfo.get('callback_id'))
                except Exception:
                    pass
                print("iter  find!")
                return True
        return False

    def rrtConnectSearch(self):
        if self.success:
            self.initInfo.get('newNode')[1].label = '► 开始'
            try:
                from bokeh.io import curdoc
                curdoc().remove_periodic_callback(self.initInfo.get('callback_id'))
            except Exception:
                pass
            return True
        if len(self.trees) == 0:
            treeI = Tree(nroot=self.nInit)
            treeG = Tree(nroot=self.nGoal)
            self.trees.append(treeI)
            self.trees.append(treeG)
            tree1 = treeI
            tree2 = treeG
        else:
            tree1 = self.trees[0]
            tree2 = self.trees[1]
        xrand = self.SampleRandomFreeFast()
        nnearest, dis = tree1.getNearest(xrand)
        nnew = self.Extend(nnearest, xrand)
        if nnew is not None:
            tree1.addNode(nnew)
            self.initInfo.get('p').rect(x=nnew.x[0], y=nnew.x[1], width=0.6, height=0.6, color='blue', alpha=1,
                                        line_color=None)
            nnears = tree2.getNearby(nnew, self.stepSize)
            if len(nnears):
                ncon = nnears[0]
                connectTree = Tree(ncon)
                self.trees.append(connectTree)
                self.success = True
                self.getPath()
                self.initInfo.get('p').line(self.path_x, self.path_y, line_width=3, color='red')
                self.initInfo.get('newNode')[1].label = '► 开始'
                try:
                    from bokeh.io import curdoc
                    curdoc().remove_periodic_callback(self.initInfo.get('callback_id'))
                except Exception:
                    pass
                return True
            nnearest, dis = tree2.getNearest(nnew.x)
            nnew2 = self.Extend(nnearest, nnew.x)
            while nnew2:
                tree2.addNode(nnew2)
                self.initInfo.get('p').rect(x=nnew2.x[0], y=nnew2.x[1], width=0.6, height=0.6, color='blue', alpha=1,
                                            line_color=None)
                nnears = tree1.getNearby(nnew2, self.stepSize)
                if len(nnears):
                    ncon = nnears[0]
                    connectTree = Tree(ncon)
                    self.trees = [tree2, tree1, connectTree]
                    self.success = True
                    self.getPath()
                    self.initInfo.get('p').line(self.path_x, self.path_y, line_width=3, color='red')
                    self.initInfo.get('newNode')[1].label = '► 开始'
                    try:
                        from bokeh.io import curdoc
                        curdoc().remove_periodic_callback(self.initInfo.get('callback_id'))
                    except Exception:
                        pass
                    return True
                nnearest = nnew2
                nnew2 = self.Extend(nnearest, nnew.x)

            # 引用类型 直接交换
            if tree1.length() > tree2.length():
                temptree = tree1
                tree1 = tree2
                tree2 = temptree
        return False

    def rrtStarSearch(self):
        if len(self.trees) == 0:
            tree = Tree(self.nInit)  # 以初始点作为树
            self.trees.append(tree)  # 树 增加节点（rrt只有一棵树）
        else:
            tree = self.trees[0]
        if self.success:
            self.initInfo.get('newNode')[1].label = '► 开始'
            try:
                from bokeh.io import curdoc
                curdoc().remove_periodic_callback(self.initInfo.get('callback_id'))
            except Exception:
                pass
            return True
        xrand = self.SampleRandomFreeFast()
        nnearest, dis = tree.getNearest(xrand)
        nnew = self.Extend(nnearest, xrand)
        if nnew is not None:
            tree.addNode(nnew)
            self.reParent(nnew, tree)
            self.reWire(nnew, tree)
            self.initInfo.get('p').rect(x=nnew.x[0], y=nnew.x[1], width=0.6, height=0.6, color='blue', alpha=1,
                                        line_color=None)
            if Node.distance(nnew, self.nGoal) < self.canACC:
                tree.addNode(self.nGoal, parent=nnew)
                self.success = True
                self.getPath()
                self.initInfo.get('p').line(self.path_x, self.path_y, line_width=3, color='red')
                self.initInfo.get('newNode')[1].label = '► 开始'
                try:
                    from bokeh.io import curdoc
                    curdoc().remove_periodic_callback(self.initInfo.get('callback_id'))
                except Exception:
                    pass
                return True
        return False

    def _CollisionPoint(self, x):
        obs = self.map.obstacles
        for ob in obs:
            if ob.get('type') == 'rectangle':
                if (ob.get('sx') <= x[0] <= ob.get('ex')) and (ob.get('sy') <= x[1] <= ob.get('ey')):
                    return True
            elif ob.get('type') == 'circle':
                cx = (ob.get('sx') + ob.get('ex')) / 2
                cy = (ob.get('sy') + ob.get('ey')) / 2
                if Node.distance([cx, cy], x) < Node.distance([ob.get('sx'), ob.get('sy')],
                                                              [ob.get('ex'), ob.get('ey')]) / 2:
                    return True
        return False

    def _CollisionLine(self, x1, x2):
        dis = Node.distance(x1, x2)
        if dis < self.DISCRETE:
            return False
        nums = int(dis / self.DISCRETE)
        direction = (np.array(x2) - np.array(x1)) / Node.distance(x1, x2)
        for i in range(nums + 1):
            x = np.add(x1, i * self.DISCRETE * direction)
            if self._CollisionPoint(x): return True
        if self._CollisionPoint(x2): return True
        return False

    # 扩展长度 父关系都处理了
    def Extend(self, nnearest, xrand, step=None):
        if not step:
            step = self.stepSize
        dis = Node.distance(nnearest, xrand)
        if dis < step:
            xnew = xrand
        else:
            dis = step
            xnew = np.array(nnearest.x) + step * (np.array(xrand) - np.array(nnearest.x)) / Node.distance(nnearest,
                                                                                                          xrand)
        if self._CollisionPoint(xnew) or self._CollisionLine(xnew, nnearest.x):
            return None
        nnew = Node(xnew, parent=nnearest, lcost=dis)
        return nnew

    # 重新找父节点
    def reParent(self, node, tree):
        nears = tree.getNearby(node)
        for n in nears:
            if self._CollisionLine(n.x, node.x):
                continue
            newl = Node.distance(n, node)
            if n.cost + newl < node.cost:
                node.parent = n
                node.lcost = newl
                node.cost = n.cost + newl

    # 修剪到最优
    def reWire(self, node, tree):
        nears = tree.getNearby(node)
        for n in nears:
            if self._CollisionLine(n.x, node.x):
                continue
            newl = Node.distance(n, node)
            if node.cost + newl < n.cost:
                n.parent = node
                n.lcost = newl
                n.cost = node.cost + newl

    def SampleRandomFreeFast(self):
        r = random.random()  # 有部分概率偏向终点 更加贪婪
        if r < self.prob:
            return self.map.pGoal
        else:
            ret = self._SampleRandom()  # 生成一个新的点 并且不会生成在 不可到达的范围内
            while self._CollisionPoint(ret):
                ret = self._SampleRandom()
        return ret

    # 生成一个新的点
    def _SampleRandom(self):
        ret = []
        for i in range(2):
            ret.append(random.random() * self.map.randLength[i] + self.map.randBias[i])
        return ret


class Node:
    def __init__(self, x, lcost=0.0, cost=float('inf'), parent=None):
        self.x = np.array(x)
        self.lcost = lcost  # 从父节点到此节点的花费
        self.cost = cost  # 初始化为多少花费 默认inf
        self.parent = parent  # 父节点
        # 更新花费
        if parent:
            self.cost = self.lcost + parent.cost

    # 获取两个点的距离
    @staticmethod
    def distance(agr1, agr2):
        argA = np.array(agr1.x) if type(agr1) == Node else np.array(agr1)
        argB = np.array(agr2.x) if type(agr2) == Node else np.array(agr2)
        return lng.norm(argA - argB)


# TODO
class Tree:
    def __init__(self, nroot):
        self.root = nroot  # 根节点
        self.nodes = [nroot]  # 节点

    # 新增一个节点
    def addNode(self, n: Node, parent: Node = None):
        if parent:
            n.parent = parent
            n.cost = n.lcost + parent.cost
        self.nodes.append(n)

    # 节点长度
    def length(self):
        return len(self.nodes)

    # 获取距离x最近的点
    def getNearest(self, x):
        dis = float('inf')
        nnearest = None
        for node in self.nodes:
            curDis = Node.distance(node, x)
            if curDis < dis:
                dis = curDis
                nnearest = node
        return nnearest, dis

    # 获取
    def getNearby(self, nto, dis=None):
        ret = []
        if dis is None:
            dis = 20.0 * math.sqrt((math.log(self.length()) / self.length()))
        for n in self.nodes:
            if Node.distance(nto, n) < dis:
                ret.append(n)
        return ret


class Map:
    def __init__(self, initInfo: dict):
        self.pInit = initInfo.get('startPoint')  # 起点
        self.pGoal = initInfo.get('endPoint')  # 终点
        self.randLength = [initInfo.get('xlen') - 1, initInfo.get('ylen') - 1]
        self.randBias = initInfo.get('randBias')
        self.obstacles = []
        # 生成地图上的不可到达点
        if initInfo.get('imType') == '矩形障碍_设置':
            with open('obstacles.json', 'r', encoding='utf-8') as f:
                import json
                obs = json.loads(f.read())
                self.obstacles = obs.get(initInfo.get('imType'))
        elif initInfo.get('imType') == '随机矩形':
            if initInfo.get('canFlashMap'):
                initInfo['canFlashMap'] = False
                xLen = initInfo.get('xlen')
                yLen = initInfo.get('ylen')
                for i in range(random.randint(15, 20)):
                    sx = random.randint(0, xLen)
                    sy = random.randint(0, yLen)
                    ex = random.randint(sx, min(xLen, sx + 30))
                    ey = random.randint(sy, min(yLen, sy + 30))
                    self.obstacles.append(
                        {
                            "type": "rectangle",
                            "sx": sx,
                            "sy": sy,
                            "ex": ex,
                            "ey": ey
                        },
                    )
            else:
                self.obstacles = initInfo.get('rrt').map.obstacles
        elif initInfo.get('imType') == '随机圆':
            if initInfo.get('canFlashMap'):
                initInfo['canFlashMap'] = False
                xLen = initInfo.get('xlen')
                yLen = initInfo.get('ylen')
                for i in range(random.randint(15, 20)):
                    sx = random.randint(0, xLen)
                    sy = random.randint(0, yLen)
                    ex = random.randint(sx, min(xLen, sx + 40))
                    ey = random.randint(sy, min(yLen, sy + 40))
                    self.obstacles.append(
                        {
                            "type": "circle",
                            "sx": sx,
                            "sy": sy,
                            "ex": ex,
                            "ey": ey
                        },
                    )
            else:
                self.obstacles = initInfo.get('rrt').map.obstacles
        elif initInfo.get('imType') == '随机矩形+随机圆':
            if initInfo.get('canFlashMap'):
                initInfo['canFlashMap'] = False
                xLen = initInfo.get('xlen')
                yLen = initInfo.get('ylen')
                for i in range(random.randint(7, 15)):
                    sx = random.randint(0, xLen)
                    sy = random.randint(0, yLen)
                    ex = random.randint(sx, min(xLen, sx + 40))
                    ey = random.randint(sy, min(yLen, sy + 40))
                    self.obstacles.append(
                        {
                            "type": "circle",
                            "sx": sx,
                            "sy": sy,
                            "ex": ex,
                            "ey": ey
                        },
                    )
                    sx = random.randint(0, xLen)
                    sy = random.randint(0, yLen)
                    ex = random.randint(sx, min(xLen, sx + 30))
                    ey = random.randint(sy, min(yLen, sy + 30))
                    self.obstacles.append(
                        {
                            "type": "rectangle",
                            "sx": sx,
                            "sy": sy,
                            "ex": ex,
                            "ey": ey
                        },
                    )
            else:
                self.obstacles = initInfo.get('rrt').map.obstacles
        # 可视化阴影
        minxLen = 6 * initInfo.get('xlen')
        minyLen = 6 * initInfo.get('ylen')
        gamaX = 1 if minxLen < 800 else 800 / minxLen
        gamaY = 1 if minyLen < 800 else 800 / minyLen
        for val in self.obstacles:
            if val.get('type') == 'rectangle':
                tmpX = []
                tmpY = []
                for i in range(val.get('sx'), val.get('ex')):
                    for j in range(val.get('sy'), val.get('ey')):
                        tmpX.append(i)
                        tmpY.append(j)
                initInfo.get('p').rect(x=tmpX, y=tmpY, width=1, height=1, color='black', alpha=1,
                                       line_color='black')  # alpha透明度
            if val.get('type') == 'circle':
                cx = (val.get('sx') + val.get('ex')) / 2
                cy = (val.get('sy') + val.get('ey')) / 2
                size = Node.distance([val.get('sx'), val.get('sy')], [val.get('ex'), val.get('ey')])
                initInfo.get('p').circle(x=cx, y=cy, size=min(gamaX, gamaY) * size,
                                         color="black", alpha=0.8)


def genMainRRT(initInfo: dict):
    rrtMap = Map(initInfo)
    if initInfo.get('title') == 'rrt 基础算法':
        rrt = RRT(_map=rrtMap, method="RRT", initInfo=initInfo)
    elif initInfo.get('title') == 'rrt* 算法':
        rrt = RRT(_map=rrtMap, method="RRT*", initInfo=initInfo)
    elif initInfo.get('title') == 'rrt-connect 算法':
        rrt = RRT(_map=rrtMap, method="RRT-Connect", initInfo=initInfo)
    initInfo['rrt'] = rrt
