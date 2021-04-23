#include<iostream>
#include<math.h>
using namespace std;
int main()
{
	double a,b,c,s,area,q,e;
loop:
	cout<<"请输入三角形的三边:"<<endl;
	cin>>a>>b>>c;
	if((b+c>a)&&(a+c>b)&&(a+b>c)){
	s=a+b+c;
	q=s/2;
	area=sqrt(q*(q-a)*(q-b)*(q-c));
	cout<<"三角形的周长是："<<s<<endl;
	cout<<"三角形的面积是："<<area<<endl;
	}
	else {
	cout<<"你输入的数不符合规范，请重新输入"<<endl; 
	goto loop;
	}
	return 0; 
}