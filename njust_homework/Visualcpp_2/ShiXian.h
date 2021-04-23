/*----9181040G0818黄海浪----第4题特殊图像效果----9181040G0818黄海浪----*/

#ifndef SHIXIAN_H_INCLUDED		//是否重复包含
#define SHIXIAN_H_INCLUDED
#include<stdlib.h>				//rand(),exit()
#include<iostream>				//输入输出流
#include<fstream>				//文件流
#include<Windows.h>				//异常自动退出时间
#include<time.h>				//加入计时器
#include"math.h"				//数学函数
#include"XinXi.h"				//包含xinxi文件
using namespace std;
unsigned int nShare;
unsigned int nWidth;

int Match(int nRed, int nGreen, int nBlue) {						//寻找与像素匹配的调色板的序号 
	long int nMax, nLength;
	int nNum = 0, nCounti;
	unsigned int nImageRed, nImageGreen, nImageBlue;
	nImageRed = (unsigned int)(straPla[0].rgbRed);				//straPla xinxi文件中的调色板
	nImageGreen = (unsigned int)(straPla[0].rgbGreen);			//straPla 每个函数都读取了文件的调色板信息 
	nImageBlue = (unsigned int)(straPla[0].rgbBlue);
	//算法……寻找与像素匹配的调色板的序号
	nMax = (nRed - nImageRed) * (nRed - nImageRed) + (nGreen - nImageGreen) * (nGreen - nImageGreen) + (nBlue - nImageBlue) * (nBlue - nImageBlue);
	for (nCounti = 0; nCounti < 256; nCounti++)
	{
		nImageRed = (unsigned int)(straPla[nCounti].rgbRed);
		nImageGreen = (unsigned int)(straPla[nCounti].rgbGreen);
		nImageBlue = (unsigned int)(straPla[nCounti].rgbBlue);
		nLength = (nRed - nImageRed) * (nRed - nImageRed) + (nGreen - nImageGreen) * (nGreen - nImageGreen) + (nBlue - nImageBlue) * (nBlue - nImageBlue);
		//for层层计算if判断求最匹配
		if (nMax > nLength)
		{
			nMax = nLength;
			nNum = nCounti;
			if (nMax == 0)
				break;
		}
	}
	return nNum;
}
/*
	柔化效果
		算法: 取像素点中心外p*p像素点 颜色 平均值作为该点像素颜色
*/
int Smooth(ifstream & infile, ofstream & outfile) {
	unsigned int nCounti, nCountj, nCountk, nCountl, nCountm, nCountn, nRed, nGreen, nBlue;
	int p, y;
	unsigned nPixel;
	clock_t startTime, endTime;
	infile.read((char*)& strHead, sizeof(strHead));
	infile.read((char*)& strInfo, sizeof(strInfo));
	//获取图片文件信息，动态建立二维数组
	nShare = strInfo.biHeight;
	nWidth = strInfo.biWidth;
	char** naImage = new char* [nShare];
	for (unsigned int i = 0; i < nShare; i++)
		naImage[i] = new char[nWidth];
	cout << endl << "图片长度: " << nWidth << "  宽度: " << nShare << endl;
	//限制系数不超过本身图像大小
	y = (nWidth < nShare ? nWidth : nShare);
	if (y <= 0) {
		cout << "图片太小，无法处理!" << endl;
		return 1;
	}
	cout << "输入所需柔化的点的长度(整数)X:" << endl << "理论大小: 0<X<=" << y << "   建议大小: 2<X<=15" << endl;
	cin >> p;
	if (p < 0 || p > y)
		return 0;
	cout << "处理中..." << endl;
	startTime = clock();
	for (nCounti = 0; nCounti < 256; nCounti++)
		infile.read((char*)& straPla[nCounti], sizeof(RGBQUAD));
	outfile.write((char*)& strHead, sizeof(strHead));
	outfile.write((char*)& strInfo, sizeof(strInfo));
	for (nCounti = 0; nCounti < 256; nCounti++)
		outfile.write((char*)& straPla[nCounti], sizeof(RGBQUAD));
	//算法处理
	for (nCountj = 0; nCountj < nShare; nCountj++)
		infile.read(&naImage[nCountj][0], nWidth);
	for (nCountk = 1; nCountk < nShare - p + 1; nCountk++)
		for (nCountl = 1; nCountl < nWidth - p + 1; nCountl++) {
			nRed = 0, nGreen = 0, nBlue = 0;
			for (nCountm = 0; nCountm < p; nCountm++)				//用p*p个点的均值柔化
				for (nCountn = 0; nCountn < p; nCountn++) {
					nPixel = (unsigned char)(naImage[nCountk - 1 + nCountm][nCountl - 1 + nCountn]);
					nRed += straPla[nPixel].rgbRed;
					nGreen += straPla[nPixel].rgbGreen;
					nBlue += straPla[nPixel].rgbBlue;
				}
			nRed = nRed / (p * p);
			nGreen = nGreen / (p * p);
			nBlue = nBlue / (p * p);
			nPixel = Match(nRed, nGreen, nBlue);					//在调色板中寻找最匹配新颜色的序号
			naImage[nCountk][nCountl] = nPixel;						//对该处的像素点用新序号赋值
		}
	//边缘处理，分三步，一步上一步右，一步右上方块
	//处理上方
	for (nCountk = nShare - p + 1; nCountk < nShare; nCountk++)
		for (nCountl = 1; nCountl < nWidth - p + 1; nCountl++) {
			nRed = 0, nGreen = 0, nBlue = 0;
			for (nCountm = 0; nCountm < nShare - nCountk; nCountm++)				//使用上方剩余点*P进行计算
				for (nCountn = 0; nCountn < p; nCountn++) {
					nPixel = (unsigned char)(naImage[nCountk - 1 + nCountm][nCountl - 1 + nCountn]);
					nRed += straPla[nPixel].rgbRed;
					nGreen += straPla[nPixel].rgbGreen;
					nBlue += straPla[nPixel].rgbBlue;
				}
			nRed = nRed / ((nShare - nCountk) * p);
			nGreen = nGreen / ((nShare - nCountk) * p);
			nBlue = nBlue / ((nShare - nCountk) * p);
			nPixel = Match(nRed, nGreen, nBlue);
			naImage[nCountk][nCountl] = nPixel;
		}
	for (nCountk = 1; nCountk < nShare - p + 1; nCountk++)
		for (nCountl = nWidth - p + 1; nCountl < nWidth; nCountl++) {
			nRed = 0, nGreen = 0, nBlue = 0;
			for (nCountm = 0; nCountm < p; nCountm++)							//使用右方剩余点*P进行计算
				for (nCountn = 0; nCountn < nWidth - nCountl; nCountn++) {
					nPixel = (unsigned char)(naImage[nCountk - 1 + nCountm][nCountl - 1 + nCountn]);
					nRed += straPla[nPixel].rgbRed;
					nGreen += straPla[nPixel].rgbGreen;
					nBlue += straPla[nPixel].rgbBlue;
				}
			nRed = nRed / ((nWidth - nCountl) * p);
			nGreen = nGreen / ((nWidth - nCountl) * p);
			nBlue = nBlue / ((nWidth - nCountl) * p);
			nPixel = Match(nRed, nGreen, nBlue);
			naImage[nCountk][nCountl] = nPixel;
		}
	for (nCountk = nShare - p + 1; nCountk < nShare; nCountk++)
		for (nCountl = nWidth - p + 1; nCountl < nWidth; nCountl++) {
			nRed = 0, nGreen = 0, nBlue = 0;
			for (nCountm = 0; nCountm < nShare - nCountk; nCountm++)			//使用右上剩余点相乘进行计算
				for (nCountn = 0; nCountn < nWidth - nCountl; nCountn++) {
					nPixel = (unsigned char)(naImage[nCountk - 1 + nCountm][nCountl - 1 + nCountn]);
					nRed += straPla[nPixel].rgbRed;
					nGreen += straPla[nPixel].rgbGreen;
					nBlue += straPla[nPixel].rgbBlue;
				}
			nRed = nRed / ((nWidth - nCountl) * (nShare - nCountk));
			nGreen = nGreen / ((nWidth - nCountl) * (nShare - nCountk));
			nBlue = nBlue / ((nWidth - nCountl) * (nShare - nCountk));
			nPixel = Match(nRed, nGreen, nBlue);
			naImage[nCountk][nCountl] = nPixel;
		}
	for (nCountj = 0; nCountj < nShare; nCountj++)
		outfile.write(&naImage[nCountj][0], nWidth);
	//释放动态创建的数组
	for (unsigned int i = 0; i < nShare; i++)
		delete[] naImage[i];
	delete[] naImage;
	endTime = clock();
	cout << "处理用时: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 1;
}

/* 锐化处理
		算法: new=original_color+m*difference(m为锐化系数,difference为相邻像素差值)
*/
int Sharp(ifstream & infile, ofstream & outfile) {
	unsigned int nCounti, nCountj, nCountk, nCountl, nRed, nBlue, nGreen, nDx = 1, nDy = 1;
	double m, x;
	clock_t startTime, endTime;
	unsigned int nPixel1, nPixel2, nPixel;
	infile.read((char*)& strHead, sizeof(strHead));						//将图片的文件头原样读出旧文件
	infile.read((char*)& strInfo, sizeof(strInfo));
	//获取图片文件信息，动态建立二维数组
	nShare = strInfo.biHeight;
	nWidth = strInfo.biWidth;
	char** naImage = new char* [nShare];
	for (unsigned int i = 0; i < nShare; i++)
		naImage[i] = new char[nWidth];
	cout << endl << "图片长度: " << nWidth << "  宽度: " << nShare << endl;
	cout << "输入锐化系数(1-10): " << endl;
	cin >> x;
	if (x < 1 || x>10)
		return 0;
	cout << "处理中..." << endl;
	startTime = clock();
	m = x / 10.0;
	for (nCounti = 0; nCounti < 256; nCounti++)
		infile.read((char*)& straPla[nCounti], sizeof(RGBQUAD));		//读取文件调色板信息
	outfile.write((char*)& strHead, sizeof(strHead));					//将图象基础信息写进输出文件
	outfile.write((char*)& strInfo, sizeof(strInfo));
	for (nCounti = 0; nCounti < 256; nCounti++)
		outfile.write((char*)& straPla[nCounti], sizeof(RGBQUAD));		//写调色板数据
	for (nCountj = 0; nCountj < nShare; nCountj++)					//锐化即是放大相邻元素的差值
		infile.read(&naImage[nCountj][0], nWidth);					//从文件中取图象数据
//图像处理算法new=original+m*difference
	for (nCountk = 1; nCountk < nShare; nCountk++)
		for (nCountl = 1; nCountl < nWidth; nCountl++) {
			nPixel1 = (unsigned char)(naImage[nCountk][nCountl]);	//取出相邻两行的数据，图象中的数据即是调色板中的序号
			nPixel2 = (unsigned char)(naImage[nCountk - nDx][nCountl - nDy]);
			nRed = straPla[nPixel1].rgbRed + m * (straPla[nPixel1].rgbRed - straPla[nPixel2].rgbRed);
			//m为锐化系数,将对应的调色板中的三种颜色分解，按照锐化公式重新计算新的颜色比重
			nGreen = straPla[nPixel1].rgbGreen + m * (straPla[nPixel1].rgbGreen - straPla[nPixel2].rgbGreen);
			nBlue = straPla[nPixel1].rgbBlue + m * (straPla[nPixel1].rgbBlue - straPla[nPixel2].rgbBlue);
			//设置颜色值上限下限
			if (nRed > 255)
				nRed = 255;
			if (nRed < 0)
				nRed = 0;
			if (nGreen > 255)
				nGreen = 255;
			if (nGreen < 0)
				nGreen = 0;
			if (nBlue > 255)
				nBlue = 255;
			if (nBlue < 0)
				nBlue = 0;
			nPixel = Match(nRed, nGreen, nBlue);					 //计算出新的颜色值后，在调色板中寻找与其最匹配的颜色序号
			naImage[nCountk][nCountl] = nPixel;						 //将寻调色板的新的序号赋值该处像素
		}
	//边缘处理左
	nCountk = 0;
	nPixel1 = (unsigned char)(naImage[nCountk][0]);
	nPixel2 = (unsigned char)(naImage[nCountk + nDx][0]);
	nRed = straPla[nPixel1].rgbRed + m * (straPla[nPixel1].rgbRed - straPla[nPixel2].rgbRed);
	nGreen = straPla[nPixel1].rgbGreen + m * (straPla[nPixel1].rgbGreen - straPla[nPixel2].rgbGreen);
	nBlue = straPla[nPixel1].rgbBlue + m * (straPla[nPixel1].rgbBlue - straPla[nPixel2].rgbBlue);
	if (nRed > 255)
		nRed = 255;
	if (nRed < 0)
		nRed = 0;
	if (nGreen > 255)
		nGreen = 255;
	if (nGreen < 0)
		nGreen = 0;
	if (nBlue > 255)
		nBlue = 255;
	if (nBlue < 0)
		nBlue = 0;
	nPixel = Match(nRed, nGreen, nBlue);
	naImage[nCountk][0] = nPixel;
	//边缘处理下
	nCountl = 0;
	nPixel1 = (unsigned char)(naImage[0][nCountl]);
	nPixel2 = (unsigned char)(naImage[0][nCountl + nDx]);
	nRed = straPla[nPixel1].rgbRed + m * (straPla[nPixel1].rgbRed - straPla[nPixel2].rgbRed);
	nGreen = straPla[nPixel1].rgbGreen + m * (straPla[nPixel1].rgbGreen - straPla[nPixel2].rgbGreen);
	nBlue = straPla[nPixel1].rgbBlue + m * (straPla[nPixel1].rgbBlue - straPla[nPixel2].rgbBlue);
	if (nRed > 255)
		nRed = 255;
	if (nRed < 0)
		nRed = 0;
	if (nGreen > 255)
		nGreen = 255;
	if (nGreen < 0)
		nGreen = 0;
	if (nBlue > 255)
		nBlue = 255;
	if (nBlue < 0)
		nBlue = 0;
	nPixel = Match(nRed, nGreen, nBlue);
	naImage[0][nCountl] = nPixel;

	for (nCountj = 0; nCountj < nShare; nCountj++)
		outfile.write(&naImage[nCountj][0], nWidth);
	//释放动态创建的数组
	for (unsigned int i = 0; i < nShare; i++)
		delete[] naImage[i];
	delete[] naImage;
	endTime = clock();
	cout << "处理用时: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 1;
}
/*浮雕效果
	算法: new_color=difference+128
*/
int Emboss(ifstream & infile, ofstream & outfile) {
	clock_t startTime, endTime;
	unsigned int nCounti, nCountj, nCountk, nCountl, nRed, nBlue, nGreen, nDx = 1, nDy = 1, nPixel1, nPixel2, nPixel;
	infile.read((char*)& strHead, sizeof(strHead));
	infile.read((char*)& strInfo, sizeof(strInfo));
	//获取图片文件信息，动态建立二维数组
	nShare = strInfo.biHeight;
	nWidth = strInfo.biWidth;
	char** naImage = new char* [nShare];
	for (unsigned int i = 0; i < nShare; i++)
		naImage[i] = new char[nWidth];
	cout << endl << "图片长度: " << nWidth << "  宽度: " << nShare << endl;
	cout << "处理中..." << endl;
	startTime = clock();
	for (nCounti = 0; nCounti < 256; nCounti++)
		infile.read((char*)& straPla[nCounti], sizeof(RGBQUAD));
	outfile.write((char*)& strHead, sizeof(strHead));
	outfile.write((char*)& strInfo, sizeof(strInfo));
	for (nCounti = 0; nCounti < 256; nCounti++)
		outfile.write((char*)& straPla[nCounti], sizeof(RGBQUAD));
	//浮雕是保留相邻元素的差值
	for (nCountj = 0; nCountj < nShare; nCountj++)
		infile.read(&naImage[nCountj][0], nWidth);
	for (nCountk = 0; nCountk < nShare - 1; nCountk++) {
		for (nCountl = 0; nCountl < nWidth - 1; nCountl++) {
			nPixel1 = (unsigned char)(naImage[nCountk][nCountl]);
			nPixel2 = (unsigned char)(naImage[nCountk + nDx][nCountl + nDy]);
			nRed = fabs(straPla[nPixel1].rgbRed - straPla[nPixel2].rgbRed + 128);		//将对应的调色板中的三种颜色分解出来，按照浮雕公式重新计算新的颜色比重
			nGreen = fabs(straPla[nPixel1].rgbGreen - straPla[nPixel2].rgbGreen + 128);
			nBlue = fabs(straPla[nPixel1].rgbBlue - straPla[nPixel2].rgbBlue + 128);
			nPixel = Match(nRed, nGreen, nBlue);										//在调色板中寻找最匹配新颜色的序号
			naImage[nCountk][nCountl] = nPixel;											//对该处的像素点用新序号赋值
		}
	}
	//边缘处理
	for (nCountl = 0; nCountl < nWidth - 1; nCountl++) {
		nPixel1 = (unsigned char)(naImage[nShare - 1][nCountl]);
		nPixel2 = (unsigned char)(naImage[nShare - 1][nCountl + nDy]);					//边上一行用该行上相邻的值对比
		nRed = fabs(straPla[nPixel1].rgbRed - straPla[nPixel2].rgbRed + 128);
		nGreen = fabs(straPla[nPixel1].rgbGreen - straPla[nPixel2].rgbGreen + 128);
		nBlue = fabs(straPla[nPixel1].rgbBlue - straPla[nPixel2].rgbBlue + 128);
		nPixel = Match(nRed, nGreen, nBlue);
		naImage[nShare - 1][nCountl] = nPixel;
	}
	for (nCountk = 0; nCountk < nShare - 1; nCountk++) {
		nPixel1 = (unsigned char)(naImage[nCountk][nCountl - 1]);
		nPixel2 = (unsigned char)(naImage[nCountk + nDx][nCountl - 1]);				//同理处理另外一个边
		nRed = fabs(straPla[nPixel1].rgbRed - straPla[nPixel2].rgbRed + 128);
		nGreen = fabs(straPla[nPixel1].rgbGreen - straPla[nPixel2].rgbGreen + 128);
		nBlue = fabs(straPla[nPixel1].rgbBlue - straPla[nPixel2].rgbBlue + 128);
		nPixel = Match(nRed, nGreen, nBlue);
		naImage[nCountk][nWidth - 1] = nPixel;
	}
	for (nCountj = 0; nCountj < nShare; nCountj++)
		outfile.write(&naImage[nCountj][0], nWidth);
	//释放动态创建的数组
	for (unsigned int i = 0; i < nShare; i++)
		delete[] naImage[i];
	delete[] naImage;
	endTime = clock();
	cout << "处理用时: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 1;
}

/*
	扩散效果
		算法:
			在像素点周围 x*x的像素块中随机一点作为当前像素值
*/
int Spread(ifstream & infile, ofstream & outfile) {
	unsigned int nCounti, nCountj, nCountk, nCountl, m, n;
	int x, y;
	clock_t startTime, endTime;
	unsigned int nPixel;
	infile.read((char*)& strHead, sizeof(strHead));
	infile.read((char*)& strInfo, sizeof(strInfo));
	//获取图片文件信息，动态建立二维数组
	nShare = strInfo.biHeight;
	nWidth = strInfo.biWidth;
	char** naImage = new char* [nShare];
	for (unsigned int i = 0; i < nShare; i++)
		naImage[i] = new char[nWidth];
	cout << endl << "图片长度: " << nWidth << "  宽度: " << nShare << endl;
	//限制系数不超过本身图像大小
	y = (nWidth < nShare ? nWidth : nShare);
	if (y <= 0) {
		cout << "图片太小，无法处理!" << endl;
		return 1;
	}
	cout << "请输入扩散系数X，越大越扩散 X范围: " << endl << "理论大小: 0<X<=" << y << "   建议大小: 2<X<=20" << endl;
	cin >> x;
	if (x <= 0 || x > y)
		return 0;
	cout << "处理中..." << endl;
	startTime = clock();
	for (nCounti = 0; nCounti < 256; nCounti++)
		infile.read((char*)& straPla[nCounti], sizeof(RGBQUAD));
	outfile.write((char*)& strHead, sizeof(strHead));
	outfile.write((char*)& strInfo, sizeof(strInfo));
	for (nCounti = 0; nCounti < 256; nCounti++)
		outfile.write((char*)& straPla[nCounti], sizeof(RGBQUAD));
	for (nCountj = 0; nCountj < nShare; nCountj++)
		infile.read(&naImage[nCountj][0], nWidth);
	for (nCountk = 0; nCountk < nShare - x + 1; nCountk++)
		for (nCountl = 0; nCountl < nWidth - x + 1; nCountl++) {
			n = rand() % x; m = rand() % x;
			naImage[nCountk][nCountl] = naImage[nCountk + n][nCountl + m];
		}
	//边缘处理，分三步，一步上一步右，一步右上方块
	//处理上方
	for (nCountk = nShare - x + 1; nCountk < nShare; nCountk++)					//边缘处理上方一行
		for (nCountl = 0; nCountl < nWidth - x + 1; nCountl++) {
			n = rand() % (nShare - nCountk); m = rand() % x;
			naImage[nCountk][nCountl] = naImage[nCountk + n][nCountl + m];
		}
	for (nCountk = 0; nCountk < nShare - x + 1; nCountk++) {					//边缘处理右边一行
		for (nCountl = nWidth - x + 1; nCountl < nWidth; nCountl++) {
			n = rand() % (nWidth - nCountl); m = rand() % x;
			naImage[nCountk][nCountl] = naImage[nCountk + m][nCountl + n];
		}
	}
	for (nCountk = nShare - x + 1; nCountk < nShare; nCountk++) {					//边缘处理右上一块
		for (nCountl = nWidth - x + 1; nCountl < nWidth; nCountl++) {
			n = rand() % (nWidth - nCountl); m = rand() % (nShare - nCountk);
			naImage[nCountk][nCountl] = naImage[nCountk + m][nCountl + n];
		}
	}
	for (nCountj = 0; nCountj < nShare; nCountj++)
		outfile.write(&naImage[nCountj][0], nWidth);

	//释放动态创建的数组
	for (unsigned int i = 0; i < nShare; i++)
		delete[] naImage[i];
	delete[] naImage;
	endTime = clock();
	cout << "处理用时: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 1;
}

/*马赛克效果
	算法: 找到一个点(x,y)，向右向上延伸(m,n)，把区域内的点分为 x块,块内每个像素颜色取其块颜色平均值
*/
int Masec(ifstream & infile, ofstream & outfile) {
	unsigned int nCounti, nCountj, nCountk, nCountl, nCountm, nCountn, nRed, nGreen, nBlue, nDx1, nDy1, n1, n2;
	int a, b, c, d, m;
	double nDx, nDy;
	clock_t startTime, endTime;
	unsigned nPixel;
	infile.read((char*)& strHead, sizeof(strHead));
	infile.read((char*)& strInfo, sizeof(strInfo));
	//获取图片文件信息，动态建立二维数组
	nShare = strInfo.biHeight;
	nWidth = strInfo.biWidth;
	char** naImage = new char* [nShare];
	for (unsigned int i = 0; i < nShare; i++)
		naImage[i] = new char[nWidth];
	cout << endl << "图片长度: " << nWidth << "  宽度: " << nShare << endl << endl;
	cout << "输入要处理图象的坐标(X,Y): " << "0<=X<" << nWidth - 10 << "    0<=Y<" << nShare - 10 << endl;
	cin >> b >> a;
	if (b >= nWidth - 10 || a >= nShare - 10 || b < 0 || a < 0)
		return 0;
	cout << "长度、宽度(右上延伸):" << "  10<长度<" << nWidth - b << "   10<宽度<" << nShare - a << endl;
	cin >> d >> c;
	if (d > nWidth - b || c > nShare - a || d <= 10 || c <= 10)
		return 0;
	cout << "马赛克效果系数x(x<-[5,20]，越小越模糊): " << endl;
	cin >> m;
	if (m < 5 || m>20)
		return 0;
	cout << "处理中..." << endl;
	startTime = clock();
	nDx = c / m;
	nDy = d / m;
	for (nCounti = 0; nCounti < 256; nCounti++)
		infile.read((char*)& straPla[nCounti], sizeof(RGBQUAD));
	outfile.write((char*)& strHead, sizeof(strHead));
	outfile.write((char*)& strInfo, sizeof(strInfo));
	for (nCounti = 0; nCounti < 256; nCounti++)
		outfile.write((char*)& straPla[nCounti], sizeof(RGBQUAD));
	for (nCountj = 0; nCountj < a; nCountj++) {
		infile.read(&naImage[nCountj][0], nWidth);					//从文件中取a行像素直接储存
		outfile.write(&naImage[nCountj][0], nWidth);
	}
	for (; nCountj < a + c; nCountj++)
		infile.read(&naImage[nCountj][0], nWidth);					//从文件中取c行像素进行变换
	for (nCountk = 0; nCountk < m; nCountk++)
		for (nCountl = 0; nCountl < m; nCountl++) {
			if (c % m - nCountk > 0) {
				nDx1 = nDx + 1; n1 = a + nCountk * nDx1;
			}
			else {
				nDx1 = nDx; n1 = a + nCountk * nDx + c % m;
			}
			if (d % m - nCountl > 0) {
				nDy1 = nDy + 1; n2 = b + nCountl * nDy1;
			}
			else {
				nDy1 = nDy; n2 = b + nCountl * nDy + d % m;
			}
			nRed = 0, nGreen = 0, nBlue = 0;
			for (nCountm = 0; nCountm < nDx1; nCountm++)
				for (nCountn = 0; nCountn < nDy1; nCountn++) {
					nPixel = (unsigned char)(naImage[n1 + nCountm][n2 + nCountn]);
					nRed += straPla[nPixel].rgbRed;
					nGreen += straPla[nPixel].rgbGreen;
					nBlue += straPla[nPixel].rgbBlue;
				}
			nRed = nRed / (nDx1 * nDy1);
			nGreen = nGreen / (nDx1 * nDy1);
			nBlue = nBlue / (nDx1 * nDy1);
			nPixel = Match(nRed, nGreen, nBlue);
			for (nCountm = 0; nCountm < nDx1; nCountm++)
				for (nCountn = 0; nCountn < nDy1; nCountn++)
					naImage[n1 + nCountm][n2 + nCountn] = nPixel;
		}
	for (nCounti = a; nCounti < a + c; nCounti++)
		outfile.write(&naImage[nCounti][0], nWidth);
	for (; nCounti < nShare; nCounti++) {
		infile.read(&naImage[nCounti][0], nWidth);
		outfile.write(&naImage[nCounti][0], nWidth);
	}
	//释放动态创建的数组
	for (unsigned int i = 0; i < nShare; i++)
		delete[] naImage[i];
	delete[] naImage;
	endTime = clock();
	cout << "处理用时: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 1;
}

int Initial(char nChoice) {								//输入所需选项后继续输入源文件与目的文件名
	char szFilena1[30], szFilena2[30];					//字符数组处理文件名字
	ifstream infile;				   					//两个对象
	ofstream outfile;
	cout << "输入的bmp文件名字(如123.bmp): ";
	cin >> szFilena1;									//输入文件名字
	cout << "输出的bmp文件名字(如321.bmp): ";
	cin >> szFilena2;									//输出文件名字
	infile.open(szFilena1, ios::binary);				//打开文件
	if (!infile) {										//判断打开是否成功
		cout << "打开文件失败,程序异常,3S后自动退出!" << endl;
		Sleep(3000);
		exit(0);
	}
	outfile.open(szFilena2, ios::binary);				//输出文件，此时未进行图像处理操作
	if (!outfile) {										//判断输出是否成功
		cout << "输出文件失败,程序异常,3S后自动退出!" << endl;
		Sleep(3000);
		exit(0);
	}
	//检查所需选项
	if (nChoice == '1')
		if (Smooth(infile, outfile))
			return 1;
		else
			return 0;
	else if (nChoice == '2')
		if (Sharp(infile, outfile))
			return 1;
		else
			return 0;
	else if (nChoice == '3')
		if (Emboss(infile, outfile))
			return 1;
		else
			return 0;
	else if (nChoice == '4')
		if (Spread(infile, outfile))
			return 1;
		else
			return 0;
	else if (nChoice == '5')
		if (Masec(infile, outfile))
			return 1;
		else
			return 0;
	//关闭文件
	infile.close();
	outfile.close();
}

#endif // SHIXIAN_H_INCLUDED
