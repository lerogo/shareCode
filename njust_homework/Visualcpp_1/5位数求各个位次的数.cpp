/*	仅供作业使用，黄海浪9181040G0818
	name:求五位数各个位次的数
	time:9-26
*/
#include<iostream>
using namespace std;
int main()
{
	int a, b, c, d, e, f;
	cout << "请输入一个五位数,以求得其各个位次的数"<<"\n";
	cin >> f;
	a = f % 10;
	b = f / 10 % 10;
	c = f / 100 % 10;
	d = f / 1000 % 10;
	e=f / 10000;
	cout << "其个位是：" << a << "\n";
	cout << "其十位是：" << b << "\n";
	cout << "其百位是：" << c << "\n";
	cout << "其千位是：" << d << "\n";
	cout << "其万位是：" << e << "\n";
	cout << "\n" << "仅供作业使用，黄海浪9181040G0818" << "\n";
	return 0;

}