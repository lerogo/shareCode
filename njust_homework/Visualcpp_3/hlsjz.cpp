#include <iostream>
#include "jz.h"
using namespace std;
void showhls() {
	cout << "请选择：" << endl;
	cout << "1:向量积" << endl;
	cout << "2:2阶行列式" << endl;
	cout << "3:3阶行列式" << endl;
	cout << "4:4阶行列式" << endl;
	cout << "5:向量数量积" << endl;
	cout << "6:向量数量积COS(X)" << endl;
	cout << "7:3*3矩阵 伴随矩阵 逆矩阵" << endl;
	cout << "8:4*4矩阵 伴随矩阵 逆矩阵" << endl;
	cout << "9:5*5矩阵 伴随矩阵" << endl;
}
void domath(char a[]) {
	if ('0' < a[0] && a[0] < '7' && !a[1]) {
		hls hls1(a[0]);
		hls1.show();
		cout << endl;
	}
	else if('6' < a[0] && a[0] < '10' && !a[1]){
		jz jz1(a[0]);
		jz1.set();
		cout << endl;
	}
	else { 
		cout << "输入错误,请重新输入！" << endl;
		cout << endl;
	}
}
int main() {
	while (1) {
		showhls();
		char xrr[100];
		cin >> xrr;
		cin.get();
		domath(xrr);
	}
	return 0;
}
