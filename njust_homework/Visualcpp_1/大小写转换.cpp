#include<iostream>
using namespace std;
int main()
{
	char x;			//字符型
	cout << "请输入一个字母以求实现转换;"<<"\n";
	cin >> x;
	if (x>= 'a'&&x <= 'z') { x -= 32; }
	else if (x>= 'A'&&x<= 'Z') { x += 32; }		//计算语句
	cout << "转换后:"<<x<<"\n";
	return 0;
}