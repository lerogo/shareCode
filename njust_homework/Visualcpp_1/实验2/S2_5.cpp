#include<iostream>
using namespace std;
int main()
{
	double a,b,c,q=0;
	char d;
	cout<<"请输入简单的运算式"<<endl;
	cin>>a>>d>>b;
	switch(d)
	{case '+':
		c=a+b;
		break;
	case '-':
		c=a-b;
		break;
	case '*':
		c=a*b;
		break;
	case '/':
		if(b!=0) c=a/b;
		else {
			q=1;
			cout<<"除数不合法"; 
		}
		break;
	default:
		cout<<"input is wrong,please input again";
		q=1;
	} 
	if(q==0) cout<<a<<d<<b<<"="<<c<<endl;
	return 0; 
}
