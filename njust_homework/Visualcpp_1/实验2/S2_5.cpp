#include<iostream>
using namespace std;
int main()
{
	double a,b,c,q=0;
	char d;
	cout<<"������򵥵�����ʽ"<<endl;
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
			cout<<"�������Ϸ�"; 
		}
		break;
	default:
		cout<<"input is wrong,please input again";
		q=1;
	} 
	if(q==0) cout<<a<<d<<b<<"="<<c<<endl;
	return 0; 
}
