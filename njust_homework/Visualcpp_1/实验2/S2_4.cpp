#include<iostream>
#include<math.h>
using namespace std;
int main()
{
	double a,b,c,d;
	cout<<"����������������һԪ���η��̵�ʵ��"<<endl;
	cout<<"����a��b��c�ֱ�Ϊ��aX^2+bX=c"<<endl; 
	cout<<"������a"<<endl; 
	cin>>a; 
	cout<<"������b"<<endl; 
	cin>>b; 
	cout<<"������c"<<endl; 
	cin>>c; 
	d=b*b-4*a*c;
	if(d>=0){
		cout<<"ʵ��1�ǣ�"<<(-b+sqrt(d))/2/a<<endl;
		cout<<"ʵ��2�ǣ�"<<(-b-sqrt(d))/2/a<<endl;
	}
	else  cout<<"��ʵ��";
	return 0; 
}
