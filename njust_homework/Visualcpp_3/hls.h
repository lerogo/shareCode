#include<iostream>
#include<math.h>
using namespace std;
class hls {
	char n;
public:
	double getsum2(double a[][2]) {
		return a[0][0] * a[1][1] - (a[0][1] * a[1][0]);
	}
	double getsum3(double a[][3]) {
		double q[2][2] = { a[1][1],a[1][2],a[2][1],a[2][2] },
			w[2][2] = { a[1][0],a[1][2],a[2][0],a[2][2] },
			e[2][2] = { a[1][0],a[1][1],a[2][0],a[2][1] };
		return a[0][0] * getsum2(q) - a[0][1] * getsum2(w) + a[0][2] * getsum2(e);
	}
	double getsum4(double a[][4]) {
		double q[3][3] = { a[1][1],a[1][2],a[1][3],a[2][1],a[2][2],a[2][3],a[3][1],a[3][2],a[3][3] },
			w[3][3] = { a[1][0],a[1][2],a[1][3],a[2][0],a[2][2],a[2][3],a[3][0],a[3][2],a[3][3] },
			e[3][3] = { a[1][0],a[1][1],a[1][3],a[2][0],a[2][1],a[2][3],a[3][0],a[3][1],a[3][3] },
			r[3][3] = { a[1][0],a[1][1],a[1][2],a[2][0],a[2][1],a[2][2],a[3][0],a[3][1],a[3][2] };
		return a[0][0] * getsum3(q) - a[0][1] * getsum3(w) + a[0][2] * getsum3(e) - a[0][3] * getsum3(r);
	}
	void getsumxl(double a[][3]) {
		double q[2][2] = { a[1][1],a[1][2],a[2][1],a[2][2] },
			w[2][2] = { a[1][0],a[1][2],a[2][0],a[2][2] },
			e[2][2] = { a[1][0],a[1][1],a[2][0],a[2][1] };
		cout << "(" << getsum2(q) << "," << -getsum2(w) << "," << getsum2(e) << ")" << endl;
	}
	double getsumsl(double a[][3]) {
		return a[1][0] * a[2][0] + a[1][1] * a[2][1] + a[1][2] * a[2][2];
	}
	double getsumcos(double a[][3]) {
		double q = sqrt(a[1][0] * a[1][0] + a[1][1] * a[1][1] + a[1][2] * a[1][2]);
		double w = sqrt(a[2][0] * a[2][0] + a[2][1] * a[2][1] + a[2][2] * a[2][2]);
		return fabs(getsumsl(a)) / q / w;
	}
	void show();
	hls(char a) {
		n = a;
	}
};
void hls::show() {
	if (n == '2') {
		double a[2][2];
		cout << "你选择了2阶行列式" << endl;
		cout << "请依次输入: " << endl;
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 2; ++j) {
				cin >> a[i][j];
			}
		}
		cout << "结果是: " << endl;
		cout << getsum2(a) << endl;
	}
	else if (n == '3') {
		int i = 0, j = 0;
		cout << "你选择了3阶行列式" << endl;
		double a[3][3];
		cout << "请依次输入: " << endl;
		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++) {
				cin >> a[i][j];
			}
		cout << "结果是: " << endl;
		cout << getsum3(a) << endl;
	}
	else if (n == '4') {
		cout << "你选择了4阶行列式" << endl;
		double a[4][4];
		cout << "请依次输入: " << endl;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				cin >> a[i][j];
			}
		}
		cout << "结果是: " << endl;
		cout << getsum4(a) << endl;
	}
	else if (n == '1') {
		cout << "你选择了向量积" << endl;
		double a[3][3] = { 0 };
		cout << "请依次输入两个坐标: " << endl;
		for (int i = 1; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				cin >> a[i][j];
			}
		}
		cout << "结果是: " << endl;
		getsumxl(a);
	}
	else if (n == '5') {
		cout << "你选择了数量积" << endl;
		double a[3][3] = { 0 };
		cout << "请依次输入两个坐标: " << endl;
		for (int i = 1; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				cin >> a[i][j];
			}
		}
		cout << "结果是: " << endl;
		cout << getsumsl(a) << endl;
	}
	else if (n == '6') {
		cout << "你选择了数量积cos" << endl;
		double a[3][3] = { 0 };
		cout << "请依次输入两个坐标: " << endl;
		for (int i = 1; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				cin >> a[i][j];
			}
		}
		cout << "结果是: " << endl;
		cout << "COS(X) = " << getsumcos(a) << endl;
	}
	else {
		cout << "输入错误，请重新输入!" << endl;
	}cout << endl;
}