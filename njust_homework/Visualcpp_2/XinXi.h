/*----9181040G0818�ƺ���----��4������ͼ��Ч��----9181040G0818�ƺ���----*/

#ifndef XINXI_H_INCLUDED				//�Ƿ��ظ�����
#define XINXI_H_INCLUDED
#include<Windows.h>						//ʹ��Windows.h����ͼ����Ϣ

RGBQUAD  straPla[256];					//256ɫ��ɫ��
BITMAPFILEHEADER  strHead;				//����strHead������
BITMAPINFOHEADER  strInfo;				//����strInfo������

/*----�ļ���Ϣ�ṹ��----*/
/*
typedef struct
{
	int  bfType;	���ͱ�־������BM
	long bfSize;	�ļ���С
	int bfReserved1;
	int bfReserved2;
	long bfOffBits;	λͼ����ƫ����
}HEAD;
*/
/*----�ļ���Ϣ�ṹ��----*/
/*
typedef  struct
{
	long biSize;	�ṹ���ֽ�����
	long biWidth;	ͼ����
	long biHeight;	ͼ��߶�
	int biPlanes;	����Ϊ1
	int biBitCount;	ÿ��������ռ������λ����������1,4,8�� 24
	long biCompress;	ѹ����ʽ
	long biSizeImage;	���ص����С
	long biXPelsPerMeter;	ˮƽ������
	long biYPelsPerMeter;	��ֱ������
	long biClrUsed;	ʹ�õ���ɫ��
	long biClrImportant;	��Ҫ��ɫ��
}INFO;
*/
/*----�ṹ��----*/
/*
typedef struct
{
	unsigned char  rgbBlue; ��ɫ��ռ����
	unsigned char  rgbGreen; ��ɫ��ռ����
	unsigned char  rgbRed; ��ɫ��ռ����
	unsigned char  rgbReserved;	�����ֽ�
}RGBQUAD;*/
#endif  //XINXI_H_INCLUDED
