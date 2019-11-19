#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# @Time    : 2019.11.20
# @Author  : lerogo
# @Blog    ：https://www.lerogo.top/

import csv
import requests
from bs4 import BeautifulSoup
sheng_name = ''
shi_name = ''
qu_name = ''
jd = ''
wd = ''


def get_csv(sheng_name,shi_name,qu_name,jd,wd):
    try:

        path = "F:\\ztflf.csv"
        with open(path, 'a+', encoding='utf-8', newline='') as f:
            csv_write = csv.writer(f)
            data_row = [sheng_name, shi_name, qu_name, jd, wd]
            csv_write.writerow(data_row)
    except Exception:
        return ''


# 获取page
def get_page(url):
    try:
        r = requests.get(url)
        r.encoding = r.apparent_encoding
        soup = BeautifulSoup(r.text, "lxml")
        # print(soup)
        sp_ul = soup.find_all('div', class_='cdiv')[0].find_all('p')
        return sp_ul
    except Exception:
        return ''


# 获取市区
def get_qu(url):
    try:
        r = requests.get('https://jingwei.supfree.net/' + url)
        r.encoding = r.apparent_encoding
        soup = BeautifulSoup(r.text, "lxml")
        sp_ul = soup.find_all('ul', class_='oul')[0].find_all('a')
        # print(sp_ul)
        return sp_ul
    except Exception:
        return ''


def get_jwd(url):
    try:
        global jd
        global wd
        r = requests.get('https://jingwei.supfree.net/' + url)
        r.encoding = r.apparent_encoding
        soup = BeautifulSoup(r.text, "lxml")
        sp_ul = soup.find_all('div', class_='cdiv')[0].find_all('p')[1].find_all('span', class_='bred botitle18')
        jd = sp_ul[0].string
        wd = sp_ul[1].string
    except Exception:
        return ''


# 判断是否是省
def isSheng(tmp):
    try:
        tmp.a.attrs['href']
        return 0
    except Exception:
        return 1


def get_loca(tmp):
    try:
        return tmp.find_all('a')
    except Exception:
        return ''


def get_name(tmp):
    return tmp.string


def get_shi_url(tmp):
    return tmp.attrs['href']


def do_qu(tmp):
    global sheng_name
    global shi_name
    global qu_name
    global jd
    global wd
    for i in range(0, len(tmp)):
        try:
            # 获取经纬度
            get_jwd(get_shi_url(tmp[i]))
            # 获取区名字
            qu_name = get_name(tmp[i])
            # 写入
            get_csv(sheng_name,shi_name,qu_name,jd,wd)
        except Exception:
            continue


def do_shi(tmp):
    global shi_name
    for i in range(0, len(tmp)):
        try:
            # 获取名字
            shi_name = get_name(tmp[i])
            # 获取进入区的链接
            url = get_shi_url(tmp[i])
            do_qu(get_qu(url))
        except Exception:
            continue

#方法1 更准
def get_test1():
    global sheng_name
    # 获取页面
    sp_ul = get_page('https://jingwei.supfree.net/')
    for i in range(0, len(sp_ul)):
        # 省会则赋值
        if isSheng(sp_ul[i]) == 1:
            sheng_name = get_name(sp_ul[i])
            print(sheng_name)
        else:
            # 对省下的每个市进行处理
            tmp = get_loca(sp_ul[i])
            do_shi(tmp)

#方法2  更快
def get_test2(url):
    try:
        url ='https://jingwei.supfree.net/mengzi.asp?id=' + str(url)
        r = requests.get(url)
        r.encoding = r.apparent_encoding
        soup = BeautifulSoup(r.text, "lxml")
        sp_ul = soup.find_all('div', class_='cdiv')[0].find_all('p')
        sp_ul_name = sp_ul[0].string
        sp_ul_jwd = sp_ul[1].find_all('span', class_='bred botitle18')
        sp_jd = sp_ul_jwd[0].string
        sp_wd = sp_ul_jwd[1].string
        sp_ul_name = sp_ul_name.split(' ')
        if(len(sp_ul_name)<3):
            get_csv(sp_ul_name[0],sp_ul_name[0],sp_ul_name[1],sp_jd,sp_wd)
        else:
            get_csv(sp_ul_name[0], sp_ul_name[1], sp_ul_name[2], sp_jd, sp_wd)
    except Exception:
        return ''

#方法1 更准
#get_test1()

#方法2 更快
for i in range(0,3182):
    get_test2(i)