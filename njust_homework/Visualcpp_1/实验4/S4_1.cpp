#include<iostream>
using namespace std;
int main()
{
	int a,b,c,x;
	cout<<"����������������"<<endl;
	cin>>a>>b;
	x=a*b;
	cout<<a<<"��"<<b<<"�����Լ��Ϊ��"<<endl;
	if(a<b){					//�ж�a,b�Ĵ�С,���ڱ�Ҫ�����½��н���
		a=a^b;
		b=a^b;
		a=a^b;
	}							//ʹ�������н���
	while(b!=0){				//�����Լ���㷨
		c=a%b;
		a=b;
		b=c;
	}
	cout<<a<<endl;
	cout<<"��С������Ϊ��"<<endl;
	cout<<x/a<<endl;
	return 0;
}
