/*	仅供作业使用，黄海浪9181040G0818
	name:九九乘法表
	time:9-26
*/
#include<iostream>
using namespace std;
int main() {
	for (int i = 1; i < 10; i++) {
		for (int j = 1; j <= i; j++) {
			cout << j << "*" << i << "=" << (i * j);
			cout << "\t";
		}
		cout << "\n";
	}
	cout << "\n" << "仅供作业使用，黄海浪9181040G0818" << "\n";
	return 0;
}