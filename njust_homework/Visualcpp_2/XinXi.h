/*----9181040G0818黄海浪----第4题特殊图像效果----9181040G0818黄海浪----*/

#ifndef XINXI_H_INCLUDED				//是否重复包含
#define XINXI_H_INCLUDED
#include<Windows.h>						//使用Windows.h代替图像信息

RGBQUAD  straPla[256];					//256色调色板
BITMAPFILEHEADER  strHead;				//声明strHead的类型
BITMAPINFOHEADER  strInfo;				//声明strInfo的类型

/*----文件信息结构体----*/
/*
typedef struct
{
	int  bfType;	类型标志，总是BM
	long bfSize;	文件大小
	int bfReserved1;
	int bfReserved2;
	long bfOffBits;	位图点阵偏移量
}HEAD;
*/
/*----文件信息结构体----*/
/*
typedef  struct
{
	long biSize;	结构体字节总数
	long biWidth;	图像宽度
	long biHeight;	图像高度
	int biPlanes;	必须为1
	int biBitCount;	每个像素所占二进制位数，可能是1,4,8或 24
	long biCompress;	压缩方式
	long biSizeImage;	像素点阵大小
	long biXPelsPerMeter;	水平像素数
	long biYPelsPerMeter;	垂直像素数
	long biClrUsed;	使用的颜色数
	long biClrImportant;	重要颜色数
}INFO;
*/
/*----结构体----*/
/*
typedef struct
{
	unsigned char  rgbBlue; 蓝色所占比重
	unsigned char  rgbGreen; 绿色所占比重
	unsigned char  rgbRed; 红色所占比重
	unsigned char  rgbReserved;	保留字节
}RGBQUAD;*/
#endif  //XINXI_H_INCLUDED
