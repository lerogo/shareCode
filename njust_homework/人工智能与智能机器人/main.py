#!/usr/bin/python3
# -*- coding: utf-8 -*-
# @time    : 2020/12/21 23:17
# @author  : lerogo
# @fileName: rrts.py
# !/usr/bin/env python3
# coding:utf-8

import numpy as np
from bokeh.models import Slider, Select, Button, NumericInput

from bokeh.plotting import figure, show, curdoc
from bokeh.layouts import column, row

from rrts import genMainRRT


def initMap(initInfo: dict):
    p = figure(title=initInfo.get('title'),
               x_axis_location="above", tools="save",
               x_range=[str(i) for i in range(initInfo.get('xlen'))],
               y_range=[str(i) for i in range(initInfo.get('ylen'))])
    p.plot_width = min(6 * initInfo.get('xlen'), 800)  # 宽度
    p.plot_height = min(6 * initInfo.get('ylen'), 800)  # 高度
    p.grid.grid_line_color = None  # color 格子边界
    p.axis.axis_line_color = None  # color 最外边 x/y轴颜色
    p.axis.major_tick_line_color = None  # 左边 针 颜色
    p.axis.major_label_text_font_size = "0px"  # x/y 字体大小
    p.axis.major_label_standoff = 0  # y轴 字体角度
    p.xaxis.major_label_orientation = np.pi / 3  # x轴 字体角度
    initInfo['xName'] = []
    initInfo['yName'] = []
    initInfo['color'] = []
    startPoint = initInfo.get('startPoint')
    endPoint = initInfo.get('endPoint')
    isInRadius: bool = lambda a, b: ((endPoint[0] - a) ** 2 + (endPoint[1] - b) ** 2) < initInfo.get('goalRadius') ** 2
    for i in range(initInfo.get('xlen')):
        for j in range(initInfo.get('ylen')):
            initInfo.get('xName').append(str(i))
            initInfo.get('yName').append(str(j))
            if startPoint[0] == i and startPoint[1] == j:
                initInfo.get('color').append('yellow')
            elif isInRadius(i, j):
                initInfo.get('color').append('red')
            else:
                initInfo.get('color').append('lightgrey')
    p.rect(x=initInfo.get('xName'), y=initInfo.get('yName'), width=0.98, height=0.98,
           color=initInfo.get('color'), alpha=1, line_color=None)
    # p.line(np.linspace(0, 4 * np.pi, 200), [initInfo.get('ylen') - 20 + 0.5 for i in range(200)], line_width=2)
    initInfo['p'] = p
    initInfo['show'] = show
    genMainRRT(initInfo)


def setInfo(**kwargs):
    """
    数据驱动对象
    这样做的目的是减少计算量 因为寻路算法 大部分时间改的是格子颜色
    """
    if 'callback_id' not in kwargs.keys():
        if newNode[1].label == '❚❚ 暂停':
            newNode[1].label = '► 开始'
            if initInfo.get('callback_id') is not None:
                curdoc().remove_periodic_callback(initInfo.get('callback_id'))
                setInfo(callback_id=None)
    for key in kwargs:
        initInfo[key] = kwargs.get(key)
    if len(set(kwargs.keys()).intersection(
            {'xlen', 'ylen', 'title', 'imType', 'goalRadius', 'startPoint', 'endPoint'})) != 0:
        initMap(initInfo)
        initInfo.get('layout').children[-1] = initInfo.get('p')


def sliderOnchange(attr, old, new):
    setInfo(
        xlen=xLenSlider.value,
        ylen=yLenSlider.value
    )


def pointOnchange(attr, old, new):
    setInfo(
        startPoint=[start_x.value, start_y.value],
        endPoint=[end_x.value, end_y.value]
    )


def reFlash():
    if '随机' in initInfo.get('imType'):
        setInfo(imType=initInfo.get('imType'), canFlashMap=True)


def buttonOnchange():
    """
    开始rrt算法 然后求color
    """
    if newNode[1].label == '► 开始':
        newNode[1].label = '❚❚ 暂停'
        callback_id = curdoc().add_periodic_callback(initInfo.get('rrt').Search, 2)
        setInfo(callback_id=callback_id)
    else:
        newNode[1].label = '► 开始'
        if initInfo.get('callback_id') is not None:
            curdoc().remove_periodic_callback(initInfo.get('callback_id'))
            setInfo(callback_id=None)


# 初始化数据
initInfo = dict(
    title='rrt 基础算法',  # 标题
    imType='矩形障碍_设置',  # 不能到达的范围
    canFlashMap=True,  # 是否能够刷新
    xlen=150,  # x长度
    ylen=150,  # y长度
    xName=[],  # 用于显示
    yName=[],  # 用于显示
    color=[],  # 颜色
    startPoint=[70, 40],  # 起点
    endPoint=[145, 145],  # 终点
    goalRadius=1,  # 半径
    randBias=[-3, -3],  # 随机树用
    rrt=None,  # rrt对象
    p=None,  # 画图对象
    layout=None,  # 给p用的对象
    callback_id=None,  # 定时器 不断计算
    newNode=None  # 上面回掉用
)
# 初始化
initMap(initInfo)
# 造控件
xLenSlider = Slider(title="x坐标格子数（步长50）", value=150, start=100, end=400, step=50)
xLenSlider.on_change('value', sliderOnchange)
yLenSlider = Slider(title="y坐标格子数（步长50）", value=150, start=100, end=400, step=50)
yLenSlider.on_change('value', sliderOnchange)
# method
method = Select(title='寻路方法', value='rrt 基础算法', options=['rrt 基础算法', 'rrt* 算法', 'rrt-connect 算法'])
method.on_change('value', lambda attr, old, new: setInfo(title=new))
# 障碍物类型
impedimentType = Select(title='障碍类型', value='矩形障碍_设置', options=['矩形障碍_设置', '随机矩形', '随机圆', '随机矩形+随机圆'])
impedimentType.on_change('value', lambda attr, old, new: setInfo(imType=new))
# 在x情况下执行 算法 新增点
newNode = [Button(label='刷新随机', width=120, button_type="primary"),
           Button(label='► 开始', width=60, button_type="primary")]
newNode[0].on_click(reFlash)
newNode[1].on_click(buttonOnchange)
setInfo(newNode=newNode)
# goal 的半径
goalRadius = Slider(title="目标点的半径", value=1, start=1, end=max(initInfo.get('xlen'), initInfo.get('ylen')) / 10, step=1)
goalRadius.on_change('value', lambda attr, old, new: setInfo(goalRadius=new))

# input test
start_x = NumericInput(title='start_x', value=min(initInfo.get('startPoint')[0], initInfo.get('xlen') - 1), low=0,
                       high=initInfo.get('xlen') - 1, width=60)
start_x.on_change('value', pointOnchange)
start_y = NumericInput(title='start_y', value=min(initInfo.get('startPoint')[1], initInfo.get('ylen') - 1), low=0,
                       high=initInfo.get('ylen') - 1, width=60)
start_y.on_change('value', pointOnchange)
end_x = NumericInput(title='end_x', value=min(initInfo.get('endPoint')[0], initInfo.get('xlen') - 1), low=0,
                     high=initInfo.get('xlen') - 1, width=60)
end_x.on_change('value', pointOnchange)
end_y = NumericInput(title='end_y', value=min(initInfo.get('endPoint')[1], initInfo.get('ylen') - 1), low=0,
                     high=initInfo.get('ylen') - 1, width=60)
end_y.on_change('value', pointOnchange)
# 造对象 显示
initInfo['layout'] = row(
    column(method, xLenSlider, yLenSlider, impedimentType, goalRadius, row(start_x, start_y, end_x, end_y),
           row(newNode)),
    initInfo.get('p'))
curdoc().add_root(initInfo.get('layout'))
curdoc().title = "RRT - 黄海浪"
