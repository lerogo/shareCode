#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# @Time    : 2019.11.20
# @Author  : lerogo
# @Blog    ：https://www.lerogo.top/

import urllib.request
import requests         
from bs4 import BeautifulSoup
import threading
import os.path
import ctypes
import random
from fake_useragent import UserAgent

global image_name
global _headers
_headers = {'User-Agent': UserAgent( path=(os.getcwd() + '/fake_useragent.json') ).random}
image_name = "undefined.png"
def save_img(img_url,dirname):
    global image_name
    #保存图片到磁盘文件夹dirname中
    try:
        if not os.path.exists(dirname):
            #不存在，重新建立
            os.makedirs(dirname)
        basename = image_name
        #拼接目录与文件名，得到图片路径
        filepath = os.path.join(dirname, basename)
        #下载图片，并保存到文件夹中
        urllib.request.urlretrieve(img_url,filepath)
    except Exception as e:
        #重新调用
        main()
    return filepath


#flag=1是使用自带爬取  flag=2为使用自己的api或者别人提供的api
def get_img_url(flag):
    global image_name
    global _headers
    if flag==1:
        #我喜欢第一页最新的，可以使用random.randint(1,5)
        img_page=1
        resp = requests.get("https://bing.ioliu.cn/?p=" + str(img_page),headers=_headers)
        soup = BeautifulSoup(resp.text, 'lxml')
        a_s = soup.find_all('a', class_='mark')
        #必应图片里面的第一页图片随机
        image_name = a_s[random.randint(0,11)].attrs['href']
        images_name = image_name.split('/')
        image_name = images_name[2]
        image_name = image_name.split('?')[0] + "_1920x1080.jpg"
        url = 'http://h1.ioliu.cn/bing/' + image_name
        return url
        
    if flag==2:
        api_img_url = ""    #这里填写api
        r = requests.get(api_img_url)       
        return r.url

# 设置图片绝对路径 filepath 所指向的图片为壁纸
def set_img_as_wallpaper(filepath):
    ctypes.windll.user32.SystemParametersInfoW(20, 0, filepath, 0)

def main():
    # 图片要被保存在的位置
    dirname = "F:\\000000000000000files\\0000000000000flies\\aaaafiles\\壁纸\\每日壁纸"
    #使用自带爬取
    img_url = get_img_url(1)
    #保存图片并得到保存地址
    filepath = save_img(img_url, dirname)
    #设置图片为壁纸
    set_img_as_wallpaper(filepath)

main()
