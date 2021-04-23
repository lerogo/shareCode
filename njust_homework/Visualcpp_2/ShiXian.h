/*----9181040G0818�ƺ���----��4������ͼ��Ч��----9181040G0818�ƺ���----*/

#ifndef SHIXIAN_H_INCLUDED		//�Ƿ��ظ�����
#define SHIXIAN_H_INCLUDED
#include<stdlib.h>				//rand(),exit()
#include<iostream>				//���������
#include<fstream>				//�ļ���
#include<Windows.h>				//�쳣�Զ��˳�ʱ��
#include<time.h>				//�����ʱ��
#include"math.h"				//��ѧ����
#include"XinXi.h"				//����xinxi�ļ�
using namespace std;
unsigned int nShare;
unsigned int nWidth;

int Match(int nRed, int nGreen, int nBlue) {						//Ѱ��������ƥ��ĵ�ɫ������ 
	long int nMax, nLength;
	int nNum = 0, nCounti;
	unsigned int nImageRed, nImageGreen, nImageBlue;
	nImageRed = (unsigned int)(straPla[0].rgbRed);				//straPla xinxi�ļ��еĵ�ɫ��
	nImageGreen = (unsigned int)(straPla[0].rgbGreen);			//straPla ÿ����������ȡ���ļ��ĵ�ɫ����Ϣ 
	nImageBlue = (unsigned int)(straPla[0].rgbBlue);
	//�㷨����Ѱ��������ƥ��ĵ�ɫ������
	nMax = (nRed - nImageRed) * (nRed - nImageRed) + (nGreen - nImageGreen) * (nGreen - nImageGreen) + (nBlue - nImageBlue) * (nBlue - nImageBlue);
	for (nCounti = 0; nCounti < 256; nCounti++)
	{
		nImageRed = (unsigned int)(straPla[nCounti].rgbRed);
		nImageGreen = (unsigned int)(straPla[nCounti].rgbGreen);
		nImageBlue = (unsigned int)(straPla[nCounti].rgbBlue);
		nLength = (nRed - nImageRed) * (nRed - nImageRed) + (nGreen - nImageGreen) * (nGreen - nImageGreen) + (nBlue - nImageBlue) * (nBlue - nImageBlue);
		//for������if�ж�����ƥ��
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
	�ữЧ��
		�㷨: ȡ���ص�������p*p���ص� ��ɫ ƽ��ֵ��Ϊ�õ�������ɫ
*/
int Smooth(ifstream & infile, ofstream & outfile) {
	unsigned int nCounti, nCountj, nCountk, nCountl, nCountm, nCountn, nRed, nGreen, nBlue;
	int p, y;
	unsigned nPixel;
	clock_t startTime, endTime;
	infile.read((char*)& strHead, sizeof(strHead));
	infile.read((char*)& strInfo, sizeof(strInfo));
	//��ȡͼƬ�ļ���Ϣ����̬������ά����
	nShare = strInfo.biHeight;
	nWidth = strInfo.biWidth;
	char** naImage = new char* [nShare];
	for (unsigned int i = 0; i < nShare; i++)
		naImage[i] = new char[nWidth];
	cout << endl << "ͼƬ����: " << nWidth << "  ���: " << nShare << endl;
	//����ϵ������������ͼ���С
	y = (nWidth < nShare ? nWidth : nShare);
	if (y <= 0) {
		cout << "ͼƬ̫С���޷�����!" << endl;
		return 1;
	}
	cout << "���������ữ�ĵ�ĳ���(����)X:" << endl << "���۴�С: 0<X<=" << y << "   �����С: 2<X<=15" << endl;
	cin >> p;
	if (p < 0 || p > y)
		return 0;
	cout << "������..." << endl;
	startTime = clock();
	for (nCounti = 0; nCounti < 256; nCounti++)
		infile.read((char*)& straPla[nCounti], sizeof(RGBQUAD));
	outfile.write((char*)& strHead, sizeof(strHead));
	outfile.write((char*)& strInfo, sizeof(strInfo));
	for (nCounti = 0; nCounti < 256; nCounti++)
		outfile.write((char*)& straPla[nCounti], sizeof(RGBQUAD));
	//�㷨����
	for (nCountj = 0; nCountj < nShare; nCountj++)
		infile.read(&naImage[nCountj][0], nWidth);
	for (nCountk = 1; nCountk < nShare - p + 1; nCountk++)
		for (nCountl = 1; nCountl < nWidth - p + 1; nCountl++) {
			nRed = 0, nGreen = 0, nBlue = 0;
			for (nCountm = 0; nCountm < p; nCountm++)				//��p*p����ľ�ֵ�ữ
				for (nCountn = 0; nCountn < p; nCountn++) {
					nPixel = (unsigned char)(naImage[nCountk - 1 + nCountm][nCountl - 1 + nCountn]);
					nRed += straPla[nPixel].rgbRed;
					nGreen += straPla[nPixel].rgbGreen;
					nBlue += straPla[nPixel].rgbBlue;
				}
			nRed = nRed / (p * p);
			nGreen = nGreen / (p * p);
			nBlue = nBlue / (p * p);
			nPixel = Match(nRed, nGreen, nBlue);					//�ڵ�ɫ����Ѱ����ƥ������ɫ�����
			naImage[nCountk][nCountl] = nPixel;						//�Ըô������ص�������Ÿ�ֵ
		}
	//��Ե������������һ����һ���ң�һ�����Ϸ���
	//�����Ϸ�
	for (nCountk = nShare - p + 1; nCountk < nShare; nCountk++)
		for (nCountl = 1; nCountl < nWidth - p + 1; nCountl++) {
			nRed = 0, nGreen = 0, nBlue = 0;
			for (nCountm = 0; nCountm < nShare - nCountk; nCountm++)				//ʹ���Ϸ�ʣ���*P���м���
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
			for (nCountm = 0; nCountm < p; nCountm++)							//ʹ���ҷ�ʣ���*P���м���
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
			for (nCountm = 0; nCountm < nShare - nCountk; nCountm++)			//ʹ������ʣ�����˽��м���
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
	//�ͷŶ�̬����������
	for (unsigned int i = 0; i < nShare; i++)
		delete[] naImage[i];
	delete[] naImage;
	endTime = clock();
	cout << "������ʱ: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 1;
}

/* �񻯴���
		�㷨: new=original_color+m*difference(mΪ��ϵ��,differenceΪ�������ز�ֵ)
*/
int Sharp(ifstream & infile, ofstream & outfile) {
	unsigned int nCounti, nCountj, nCountk, nCountl, nRed, nBlue, nGreen, nDx = 1, nDy = 1;
	double m, x;
	clock_t startTime, endTime;
	unsigned int nPixel1, nPixel2, nPixel;
	infile.read((char*)& strHead, sizeof(strHead));						//��ͼƬ���ļ�ͷԭ���������ļ�
	infile.read((char*)& strInfo, sizeof(strInfo));
	//��ȡͼƬ�ļ���Ϣ����̬������ά����
	nShare = strInfo.biHeight;
	nWidth = strInfo.biWidth;
	char** naImage = new char* [nShare];
	for (unsigned int i = 0; i < nShare; i++)
		naImage[i] = new char[nWidth];
	cout << endl << "ͼƬ����: " << nWidth << "  ���: " << nShare << endl;
	cout << "������ϵ��(1-10): " << endl;
	cin >> x;
	if (x < 1 || x>10)
		return 0;
	cout << "������..." << endl;
	startTime = clock();
	m = x / 10.0;
	for (nCounti = 0; nCounti < 256; nCounti++)
		infile.read((char*)& straPla[nCounti], sizeof(RGBQUAD));		//��ȡ�ļ���ɫ����Ϣ
	outfile.write((char*)& strHead, sizeof(strHead));					//��ͼ�������Ϣд������ļ�
	outfile.write((char*)& strInfo, sizeof(strInfo));
	for (nCounti = 0; nCounti < 256; nCounti++)
		outfile.write((char*)& straPla[nCounti], sizeof(RGBQUAD));		//д��ɫ������
	for (nCountj = 0; nCountj < nShare; nCountj++)					//�񻯼��ǷŴ�����Ԫ�صĲ�ֵ
		infile.read(&naImage[nCountj][0], nWidth);					//���ļ���ȡͼ������
//ͼ�����㷨new=original+m*difference
	for (nCountk = 1; nCountk < nShare; nCountk++)
		for (nCountl = 1; nCountl < nWidth; nCountl++) {
			nPixel1 = (unsigned char)(naImage[nCountk][nCountl]);	//ȡ���������е����ݣ�ͼ���е����ݼ��ǵ�ɫ���е����
			nPixel2 = (unsigned char)(naImage[nCountk - nDx][nCountl - nDy]);
			nRed = straPla[nPixel1].rgbRed + m * (straPla[nPixel1].rgbRed - straPla[nPixel2].rgbRed);
			//mΪ��ϵ��,����Ӧ�ĵ�ɫ���е�������ɫ�ֽ⣬�����񻯹�ʽ���¼����µ���ɫ����
			nGreen = straPla[nPixel1].rgbGreen + m * (straPla[nPixel1].rgbGreen - straPla[nPixel2].rgbGreen);
			nBlue = straPla[nPixel1].rgbBlue + m * (straPla[nPixel1].rgbBlue - straPla[nPixel2].rgbBlue);
			//������ɫֵ��������
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
			nPixel = Match(nRed, nGreen, nBlue);					 //������µ���ɫֵ���ڵ�ɫ����Ѱ��������ƥ�����ɫ���
			naImage[nCountk][nCountl] = nPixel;						 //��Ѱ��ɫ����µ���Ÿ�ֵ�ô�����
		}
	//��Ե������
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
	//��Ե������
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
	//�ͷŶ�̬����������
	for (unsigned int i = 0; i < nShare; i++)
		delete[] naImage[i];
	delete[] naImage;
	endTime = clock();
	cout << "������ʱ: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 1;
}
/*����Ч��
	�㷨: new_color=difference+128
*/
int Emboss(ifstream & infile, ofstream & outfile) {
	clock_t startTime, endTime;
	unsigned int nCounti, nCountj, nCountk, nCountl, nRed, nBlue, nGreen, nDx = 1, nDy = 1, nPixel1, nPixel2, nPixel;
	infile.read((char*)& strHead, sizeof(strHead));
	infile.read((char*)& strInfo, sizeof(strInfo));
	//��ȡͼƬ�ļ���Ϣ����̬������ά����
	nShare = strInfo.biHeight;
	nWidth = strInfo.biWidth;
	char** naImage = new char* [nShare];
	for (unsigned int i = 0; i < nShare; i++)
		naImage[i] = new char[nWidth];
	cout << endl << "ͼƬ����: " << nWidth << "  ���: " << nShare << endl;
	cout << "������..." << endl;
	startTime = clock();
	for (nCounti = 0; nCounti < 256; nCounti++)
		infile.read((char*)& straPla[nCounti], sizeof(RGBQUAD));
	outfile.write((char*)& strHead, sizeof(strHead));
	outfile.write((char*)& strInfo, sizeof(strInfo));
	for (nCounti = 0; nCounti < 256; nCounti++)
		outfile.write((char*)& straPla[nCounti], sizeof(RGBQUAD));
	//�����Ǳ�������Ԫ�صĲ�ֵ
	for (nCountj = 0; nCountj < nShare; nCountj++)
		infile.read(&naImage[nCountj][0], nWidth);
	for (nCountk = 0; nCountk < nShare - 1; nCountk++) {
		for (nCountl = 0; nCountl < nWidth - 1; nCountl++) {
			nPixel1 = (unsigned char)(naImage[nCountk][nCountl]);
			nPixel2 = (unsigned char)(naImage[nCountk + nDx][nCountl + nDy]);
			nRed = fabs(straPla[nPixel1].rgbRed - straPla[nPixel2].rgbRed + 128);		//����Ӧ�ĵ�ɫ���е�������ɫ�ֽ���������ո���ʽ���¼����µ���ɫ����
			nGreen = fabs(straPla[nPixel1].rgbGreen - straPla[nPixel2].rgbGreen + 128);
			nBlue = fabs(straPla[nPixel1].rgbBlue - straPla[nPixel2].rgbBlue + 128);
			nPixel = Match(nRed, nGreen, nBlue);										//�ڵ�ɫ����Ѱ����ƥ������ɫ�����
			naImage[nCountk][nCountl] = nPixel;											//�Ըô������ص�������Ÿ�ֵ
		}
	}
	//��Ե����
	for (nCountl = 0; nCountl < nWidth - 1; nCountl++) {
		nPixel1 = (unsigned char)(naImage[nShare - 1][nCountl]);
		nPixel2 = (unsigned char)(naImage[nShare - 1][nCountl + nDy]);					//����һ���ø��������ڵ�ֵ�Ա�
		nRed = fabs(straPla[nPixel1].rgbRed - straPla[nPixel2].rgbRed + 128);
		nGreen = fabs(straPla[nPixel1].rgbGreen - straPla[nPixel2].rgbGreen + 128);
		nBlue = fabs(straPla[nPixel1].rgbBlue - straPla[nPixel2].rgbBlue + 128);
		nPixel = Match(nRed, nGreen, nBlue);
		naImage[nShare - 1][nCountl] = nPixel;
	}
	for (nCountk = 0; nCountk < nShare - 1; nCountk++) {
		nPixel1 = (unsigned char)(naImage[nCountk][nCountl - 1]);
		nPixel2 = (unsigned char)(naImage[nCountk + nDx][nCountl - 1]);				//ͬ��������һ����
		nRed = fabs(straPla[nPixel1].rgbRed - straPla[nPixel2].rgbRed + 128);
		nGreen = fabs(straPla[nPixel1].rgbGreen - straPla[nPixel2].rgbGreen + 128);
		nBlue = fabs(straPla[nPixel1].rgbBlue - straPla[nPixel2].rgbBlue + 128);
		nPixel = Match(nRed, nGreen, nBlue);
		naImage[nCountk][nWidth - 1] = nPixel;
	}
	for (nCountj = 0; nCountj < nShare; nCountj++)
		outfile.write(&naImage[nCountj][0], nWidth);
	//�ͷŶ�̬����������
	for (unsigned int i = 0; i < nShare; i++)
		delete[] naImage[i];
	delete[] naImage;
	endTime = clock();
	cout << "������ʱ: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 1;
}

/*
	��ɢЧ��
		�㷨:
			�����ص���Χ x*x�����ؿ������һ����Ϊ��ǰ����ֵ
*/
int Spread(ifstream & infile, ofstream & outfile) {
	unsigned int nCounti, nCountj, nCountk, nCountl, m, n;
	int x, y;
	clock_t startTime, endTime;
	unsigned int nPixel;
	infile.read((char*)& strHead, sizeof(strHead));
	infile.read((char*)& strInfo, sizeof(strInfo));
	//��ȡͼƬ�ļ���Ϣ����̬������ά����
	nShare = strInfo.biHeight;
	nWidth = strInfo.biWidth;
	char** naImage = new char* [nShare];
	for (unsigned int i = 0; i < nShare; i++)
		naImage[i] = new char[nWidth];
	cout << endl << "ͼƬ����: " << nWidth << "  ���: " << nShare << endl;
	//����ϵ������������ͼ���С
	y = (nWidth < nShare ? nWidth : nShare);
	if (y <= 0) {
		cout << "ͼƬ̫С���޷�����!" << endl;
		return 1;
	}
	cout << "��������ɢϵ��X��Խ��Խ��ɢ X��Χ: " << endl << "���۴�С: 0<X<=" << y << "   �����С: 2<X<=20" << endl;
	cin >> x;
	if (x <= 0 || x > y)
		return 0;
	cout << "������..." << endl;
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
	//��Ե������������һ����һ���ң�һ�����Ϸ���
	//�����Ϸ�
	for (nCountk = nShare - x + 1; nCountk < nShare; nCountk++)					//��Ե�����Ϸ�һ��
		for (nCountl = 0; nCountl < nWidth - x + 1; nCountl++) {
			n = rand() % (nShare - nCountk); m = rand() % x;
			naImage[nCountk][nCountl] = naImage[nCountk + n][nCountl + m];
		}
	for (nCountk = 0; nCountk < nShare - x + 1; nCountk++) {					//��Ե�����ұ�һ��
		for (nCountl = nWidth - x + 1; nCountl < nWidth; nCountl++) {
			n = rand() % (nWidth - nCountl); m = rand() % x;
			naImage[nCountk][nCountl] = naImage[nCountk + m][nCountl + n];
		}
	}
	for (nCountk = nShare - x + 1; nCountk < nShare; nCountk++) {					//��Ե��������һ��
		for (nCountl = nWidth - x + 1; nCountl < nWidth; nCountl++) {
			n = rand() % (nWidth - nCountl); m = rand() % (nShare - nCountk);
			naImage[nCountk][nCountl] = naImage[nCountk + m][nCountl + n];
		}
	}
	for (nCountj = 0; nCountj < nShare; nCountj++)
		outfile.write(&naImage[nCountj][0], nWidth);

	//�ͷŶ�̬����������
	for (unsigned int i = 0; i < nShare; i++)
		delete[] naImage[i];
	delete[] naImage;
	endTime = clock();
	cout << "������ʱ: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 1;
}

/*������Ч��
	�㷨: �ҵ�һ����(x,y)��������������(m,n)���������ڵĵ��Ϊ x��,����ÿ��������ɫȡ�����ɫƽ��ֵ
*/
int Masec(ifstream & infile, ofstream & outfile) {
	unsigned int nCounti, nCountj, nCountk, nCountl, nCountm, nCountn, nRed, nGreen, nBlue, nDx1, nDy1, n1, n2;
	int a, b, c, d, m;
	double nDx, nDy;
	clock_t startTime, endTime;
	unsigned nPixel;
	infile.read((char*)& strHead, sizeof(strHead));
	infile.read((char*)& strInfo, sizeof(strInfo));
	//��ȡͼƬ�ļ���Ϣ����̬������ά����
	nShare = strInfo.biHeight;
	nWidth = strInfo.biWidth;
	char** naImage = new char* [nShare];
	for (unsigned int i = 0; i < nShare; i++)
		naImage[i] = new char[nWidth];
	cout << endl << "ͼƬ����: " << nWidth << "  ���: " << nShare << endl << endl;
	cout << "����Ҫ����ͼ�������(X,Y): " << "0<=X<" << nWidth - 10 << "    0<=Y<" << nShare - 10 << endl;
	cin >> b >> a;
	if (b >= nWidth - 10 || a >= nShare - 10 || b < 0 || a < 0)
		return 0;
	cout << "���ȡ����(��������):" << "  10<����<" << nWidth - b << "   10<���<" << nShare - a << endl;
	cin >> d >> c;
	if (d > nWidth - b || c > nShare - a || d <= 10 || c <= 10)
		return 0;
	cout << "������Ч��ϵ��x(x<-[5,20]��ԽСԽģ��): " << endl;
	cin >> m;
	if (m < 5 || m>20)
		return 0;
	cout << "������..." << endl;
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
		infile.read(&naImage[nCountj][0], nWidth);					//���ļ���ȡa������ֱ�Ӵ���
		outfile.write(&naImage[nCountj][0], nWidth);
	}
	for (; nCountj < a + c; nCountj++)
		infile.read(&naImage[nCountj][0], nWidth);					//���ļ���ȡc�����ؽ��б任
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
	//�ͷŶ�̬����������
	for (unsigned int i = 0; i < nShare; i++)
		delete[] naImage[i];
	delete[] naImage;
	endTime = clock();
	cout << "������ʱ: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 1;
}

int Initial(char nChoice) {								//��������ѡ����������Դ�ļ���Ŀ���ļ���
	char szFilena1[30], szFilena2[30];					//�ַ����鴦���ļ�����
	ifstream infile;				   					//��������
	ofstream outfile;
	cout << "�����bmp�ļ�����(��123.bmp): ";
	cin >> szFilena1;									//�����ļ�����
	cout << "�����bmp�ļ�����(��321.bmp): ";
	cin >> szFilena2;									//����ļ�����
	infile.open(szFilena1, ios::binary);				//���ļ�
	if (!infile) {										//�жϴ��Ƿ�ɹ�
		cout << "���ļ�ʧ��,�����쳣,3S���Զ��˳�!" << endl;
		Sleep(3000);
		exit(0);
	}
	outfile.open(szFilena2, ios::binary);				//����ļ�����ʱδ����ͼ�������
	if (!outfile) {										//�ж�����Ƿ�ɹ�
		cout << "����ļ�ʧ��,�����쳣,3S���Զ��˳�!" << endl;
		Sleep(3000);
		exit(0);
	}
	//�������ѡ��
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
	//�ر��ļ�
	infile.close();
	outfile.close();
}

#endif // SHIXIAN_H_INCLUDED
