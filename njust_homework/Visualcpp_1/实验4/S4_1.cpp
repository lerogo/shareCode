#include<iostream>
using namespace std;
int main()
{
	int a,b,c,x;
	cout<<"请输入两个正整数"<<endl;
	cin>>a>>b;
	x=a*b;
	cout<<a<<"与"<<b<<"的最大公约数为："<<endl;
	if(a<b){					//判断a,b的大小,并在必要条件下进行交换
		a=a^b;
		b=a^b;
		a=a^b;
	}							//使用异或进行交换
	while(b!=0){				//求最大公约数算法
		c=a%b;
		a=b;
		b=c;
	}
	cout<<a<<endl;
	cout<<"最小公倍数为："<<endl;
	cout<<x/a<<endl;
	return 0;
}
