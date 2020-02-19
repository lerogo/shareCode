#!/bin/bash
# -*- coding: utf-8 -*-
# @Time    : 2020.02.19
# @Author  : lerogo
# @Blog    ：https://blog.lerogo.top/

#三条命令
#openssl ecparam -genkey -name secp384r1 | openssl ec -out domain.key  #生成key
#openssl req -new -sha256 -key domain-ecc.key -nodes -out domain.csr -outform pem #生成csr
#使用自己csr 生成cert
#certbot certonly --csr domain.csr --manual --preferred-challenges dns --server https://acme-v02.api.letsencrypt.org/directory

#0000_cert.pem  - crt.pem
#0000_chain.pem - chain.pem
#0001_chain.pem - fullchain.pem
#domain.key     - privatekey

#获取绝对脚本路径目录
cur_dir=$(cd "$(dirname "$0")"; pwd)
#创建文件夹
if [ ! -d "cert/" ];then
mkdir cert
fi;

echo
echo "------------------------  生成key  ------------------------"
printf "请输入key的名称（例:private.key)[默认：private.key]: "
read keyname
if [ -z "${keyname}" ]; then
	keyname="private.key"
fi;
echo
echo "key的名称:${keyname}"
openssl ecparam -genkey -name secp384r1 | openssl ec -out "${keyname}"
if [ -f "${keyname}" ]; then
	mv -f "${keyname}" "cert/"
	echo "生成key成功，key的地址:${cur_dir}/cert/${keyname}"
	echo
else
	echo "生成key失败，请检查……"
	exit -1;
fi

echo "------------------------  生成csr  ------------------------"
printf "请输入csr的名称（例:domain-ecc.csr）[默认：domain-ecc.csr]: "
read csrname
if [ -z "${csrname}" ]; then
	csrname="domain-ecc.csr"
fi;
echo 
echo "csr的名称:${csrname}"
echo "接下来要手动填写信息啦，而且是英文呢，真是顶不住呢……"
echo
printf "按下回车继续哦~"
read
openssl req -new -sha256 -key "${cur_dir}/cert/${keyname}" -nodes -out "${csrname}" -outform pem

if [ -f "${csrname}" ]; then
	echo "生成csr成功，csr的地址:${cur_dir}/${csrname}"
	echo
else
	echo "生成csr失败，请检查……"
	exit -1;
fi


echo "------------------------  生成pem  ------------------------"
echo "好了好了，马上开始申请证书"
echo
echo "过程中会添加txt解析，请添加后再回车确认！！ "
echo
echo "按回车再继续哦……"
read

certbot certonly --csr ${csrname} --manual --preferred-challenges dns --server https://acme-v02.api.letsencrypt.org/directory

if [ -f "0000_cert.pem" -a -f "0000_chain.pem" -a -f "0001_chain.pem" ]; then

	mv -f "0000_cert.pem" "cert/crt.pem"
	mv -f "0000_chain.pem" "cert/chain.pem"
	mv -f "0001_chain.pem" "cert/fullchain.pem"
	echo
	echo "生成证书成功！可以愉快地使用啦，证书地址如下："
	echo "${cur_dir}/cert/crt.pem"
	echo "${cur_dir}/cert/chain.pem"
	echo "${cur_dir}/cert/fullchain.pem"
	echo
else
	echo "生成证书失败，请检查……"
	exit -1;
fi

echo "------------------------  所有文件  ------------------------"
echo "${cur_dir}/cert/${keyname}"
echo "${cur_dir}/cert/crt.pem"
echo "${cur_dir}/cert/chain.pem"
echo "${cur_dir}/cert/fullchain.pem"
echo "${cur_dir}/${csrname}"
echo