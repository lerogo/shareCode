#include <iostream>
#include "jz.h"
using namespace std;
void showhls() {
	cout << "��ѡ��" << endl;
	cout << "1:������" << endl;
	cout << "2:2������ʽ" << endl;
	cout << "3:3������ʽ" << endl;
	cout << "4:4������ʽ" << endl;
	cout << "5:����������" << endl;
	cout << "6:����������COS(X)" << endl;
	cout << "7:3*3���� ������� �����" << endl;
	cout << "8:4*4���� ������� �����" << endl;
	cout << "9:5*5���� �������" << endl;
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
		cout << "�������,���������룡" << endl;
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
