#include <iostream>
#include<math.h>
#include "hls.h"
class jz {
	char n;
public:
	double bshls(double a[][3]);
	double bshls(double a[][4]);
	double bshls(double a[][5]);
	jz(char a) {
		n = a;
	}
	void set();
};
void jz::set() {
	if (n == '7') {
		int i = 0, j = 0;
		cout << "你选择了3阶矩阵" << endl;
		double a[3][3];
		cout << "请依次输入: " << endl;
		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++) {
				cin >> a[i][j];
			}
		cout << "结果是: " << endl;
		bshls(a);
	}
	else if (n == '8') {
		int i = 0, j = 0;
		cout << "你选择了4阶矩阵" << endl;
		double a[4][4];
		cout << "请依次输入: " << endl;
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++) {
				cin >> a[i][j];
			}
		cout << "结果是: " << endl;
		bshls(a);
	}
	else if (n == '9') {
		cout << "你选择了5阶矩阵" << endl;
		double a[5][5];
		cout << "请依次输入: " << endl;
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				cin >> a[i][j];
			}
		}
		cout << "结果是: " << endl;
		bshls(a);
	}
}
double jz::bshls(double a[][3]) {
	hls hls1(0);
	double AA=hls1.getsum3(a);
	double arr[9][4];
	int e = 0, r = 0;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 3; ++k) {
				for (int p = 0; p < 3; ++p) {
					if (k != j && p != i) {
						if ((k + p) % 2 == 0) {
							arr[e][r++] = a[k][p];
						}
						else {
							arr[e][r++] = -a[k][p];
						}
					}
					if (r == 4) {
						r = 0;
						++e;
					}
				}
			}
		}
	}
	double b[2][2];
	double c[9];
	int ee = 0, rr = 0;
	for (ee=0; ee < 9; ++ee) {
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 2; ++j,++rr) {
				b[i][j] = arr[ee][rr];
			}
		}
		rr = 0;
		c[ee] = hls1.getsum2(b);
	}
	double drr[3][3];
	ee = 0;
	cout << "伴随矩阵A*为: " << endl;
	for (int t = 0; t < 3; t++) {
		for (int y = 0; y < 3; y++) {
			drr[t][y] = c[ee++];
			cout << drr[t][y] << "  ";
		}
		cout << endl;
	}
	cout << "A的行列式为: " << endl<<AA<<endl;
	if (AA == 0) {
		cout << "行列式为0" << endl;
		return 0;
	}
	cout << "逆矩阵A-为: " << endl;
	for (int t = 0; t < 3; t++) {
		for (int y = 0; y < 3; y++) {
			cout << drr[t][y]/AA<< "  ";
		}
		cout << endl;
	}
	return 0;
}
double jz::bshls(double a[][4]) {
	hls hls1(0);
	double AA = hls1.getsum4(a);
	double arr[16][9];
	int e = 0, r = 0;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 4; ++k) {
				for (int p = 0; p < 4; ++p) {
					if (k != j && p != i) {
						if ((k + p) % 2 == 0) {
							arr[e][r++] = a[k][p];
						}
						else {
							arr[e][r++] = -a[k][p];
						}
					}
					if (r == 9) {
						r = 0;
						++e;
					}
				}
			}
		}
	}
	double b[3][3];
	double c[16];
	int ee = 0, rr = 0;
	for (ee = 0; ee < 16; ++ee) {
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j, ++rr) {
				b[i][j] = arr[ee][rr];
			}
		}
		rr = 0;
		c[ee] = hls1.getsum3(b);
	}
	double drr[4][4];
	ee = 0;
	cout << "伴随矩阵A*为: " << endl;
	for (int t = 0; t < 4; t++) {
		for (int y = 0; y < 4; y++) {
			drr[t][y] = c[ee++];
			cout << drr[t][y] << "  ";
		}
		cout << endl;
	}
	cout << "A的行列式为: " << endl << AA << endl;
	if (AA == 0) {
		cout << "行列式为0" << endl;
		return 0;
	}
	cout << "逆矩阵A-为: " << endl;
	for (int t = 0; t < 4; t++) {
		for (int y = 0; y < 4; y++) {
			cout << drr[t][y] / AA << "  ";
		}
		cout << endl;
	}
	return 0;
}
double jz::bshls(double a[][5]) {
	hls hls1(0);
	double arr[25][16];
	int e = 0, r = 0;
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			for (int k = 0; k < 5; ++k) {
				for (int p = 0; p < 5; ++p) {
					if (k != j && p != i) {
						if ((k + p) % 2 == 0) {
							arr[e][r++] = a[k][p];
						}
						else {
							arr[e][r++] = -a[k][p];
						}
					}
					if (r == 16) {
						r = 0;
						++e;
					}
				}
			}
		}
	}
	double b[4][4];
	double c[25];
	int ee = 0, rr = 0;
	for (ee = 0; ee < 25; ++ee) {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j, ++rr) {
				b[i][j] = arr[ee][rr];
			}
		}
		rr = 0;
		c[ee] = hls1.getsum4(b);
	}
	double drr[5][5];
	ee = 0;
	cout << "伴随矩阵A*为: " << endl;
	for (int t = 0; t < 5; t++) {
		for (int y = 0; y < 5; y++) {
			drr[t][y] = c[ee++];
			cout << drr[t][y] << "  ";
		}
		cout << endl;
	}
	cout << "因为5阶行列式没有写算法," << endl <<
		"求逆需要大家自行加上哦!" << endl<<"相信你们！"<<endl;
	return 0;
}