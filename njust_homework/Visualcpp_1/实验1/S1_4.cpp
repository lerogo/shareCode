#include<iostream>
#include<math.h>
using namespace std;
int main()
{
	double a,b,c,s,area,q,e;
loop:
	cout<<"�����������ε�����:"<<endl;
	cin>>a>>b>>c;
	if((b+c>a)&&(a+c>b)&&(a+b>c)){
	s=a+b+c;
	q=s/2;
	area=sqrt(q*(q-a)*(q-b)*(q-c));
	cout<<"�����ε��ܳ��ǣ�"<<s<<endl;
	cout<<"�����ε�����ǣ�"<<area<<endl;
	}
	else {
	cout<<"��������������Ϲ淶������������"<<endl; 
	goto loop;
	}
	return 0; 
}