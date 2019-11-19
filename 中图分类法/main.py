#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# @Time    : 2019.11.20
# @Author  : lerogo
# @Blog    ：https://www.lerogo.top/

import csv
import requests
from bs4 import BeautifulSoup


def get_code(sp_t):
    try:
        #print(sp_t.span.string)
        return sp_t.span.string
    except Exception:
        return ""


def get_name(sp_t):
    try:
        #print(sp_t.a.string)
        return sp_t.a.string
    except Exception:
        return ""


def get_url(sp_t):
    try:
        #print(sp_t.a.attrs['href'])
        return sp_t.a.attrs['href']
    except Exception:
        return ""


def get_page(url):
    try:
        r = requests.get(url)
        r.encoding = "utf-8"
        soup = BeautifulSoup(r.text, "lxml")
        sp_ul = soup.find_all('ul', id='list')[0].find_all('li')
        # print(sp_ul)
        return sp_ul
    except Exception:
        return ""


def get_csv(code, name, last_code, url):
    path = "ztflf.csv"
    with open(path, 'a+',encoding='utf-8',newline='') as f:
        csv_write = csv.writer(f)
        data_row = [code, name, last_code, url]
        csv_write.writerow(data_row)


def get_son(url, last_code=-1):
    tmp = get_page(url)
    if tmp == "":
        return
    print(tmp)
    for i in range(0, len(tmp)):
        code = get_code(tmp[i])
        name = get_name(tmp[i])
        sonurl = get_url(tmp[i])
        get_csv(code, name, last_code, sonurl)
        get_son(sonurl, code)

get_son('http://ztflh.com/')
