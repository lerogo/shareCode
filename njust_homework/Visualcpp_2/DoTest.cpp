/*----9181040G0818黄海浪----第4题特殊图像效果----9181040G0818黄海浪----*/

#include<stdlib.h>						//exit()
#include<iostream>						//输入输出流
#include<Windows.h>						//异常自动退出时间
#include"XinXi.h"
#include"ShiXian.h"
using namespace std;

//函数的声明
int Match(int nRed, int nGreen, int nBlue);						//寻找与像素匹配的调色板的序号
int Smooth(ifstream& infile, ofstream& outfile);				//柔化效果
int Sharp(ifstream& infile, ofstream& outfile);					//锐化处理
int Emboss(ifstream& infile, ofstream& outfile);				//浮雕效果
int Spread(ifstream& infile, ofstream& outfile);				//扩散效果
int Masec(ifstream& infile, ofstream& outfile);					//马赛克效果
int Initial(char nChoice);										//初始化图像文件

//显示选项
void show() {
	cout << "请选择: " << endl;
	cout << "\n\t1. 柔化" << endl;
	cout << "\n\t2. 锐化" << endl;
	cout << "\n\t3. 浮雕" << endl;
	cout << "\n\t4. 扩散" << endl;
	cout << "\n\t5. 马赛克" << endl;
	cout << "\n\t6. 退出" << endl;
}

//对输入进行操作
int set(char nChoice[]) {
	if ('0' < nChoice[0] && nChoice[0] < '6' && !nChoice[1]) {
		if (Initial(nChoice[0]))
			cout << endl << "处理完成!" << endl << endl;
		else
			cout << endl << "输入错误或处理失败!" << endl << endl;
	}
	else if (nChoice[0] == '6' && !nChoice[1]) {
		cout << "选择退出,3S后自动退出!" << endl;
		Sleep(3000);
		exit(1);
	}
	else {
		cout << "输入错误，请重新输入！" << endl;
	}
}

int main() {
	while (1) {
		char nChoice[100];					//使用字符数组避免输入多个导致程序多次输入错误
		show();								//显示选项
		cin >> nChoice;						//输入选项
		set(nChoice);						//操作
	}
	return 0;
}
