#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# @Time    : 2019.12.31
# @Author  : lerogo
# @Blog    ：https://www.lerogo.top/
# 练练手
import base64
import pyperclip
import sys
def getBase64():
    try:
        if len(sys.argv) < 2:
            url = input("请输入图片路径：")
            if url == "":
                raise Exception(-1)
        else:
            url = sys.argv[1]
        with open(url, 'rb') as f:
            base64_data = base64.b64encode(f.read())
            outurl = 'data:image/' + url[-3:] + ';base64,' + base64_data.decode();
            pyperclip.copy(outurl)
            print("已经将图片转为base64并粘贴到剪切板！")
    except Exception as e:
        if e.args[0] == -1:
            print("请输入转换图片路径！")
        else:
            print("run error: "+e.__str__())
getBase64()
