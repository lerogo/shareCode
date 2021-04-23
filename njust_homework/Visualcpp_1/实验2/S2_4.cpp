#include<iostream>
#include<math.h>
using namespace std;
int main()
{
	double a,b,c,d;
	cout<<"请输入三个数以求一元二次方程的实根"<<endl;
	cout<<"其中a，b，c分别为：aX^2+bX=c"<<endl; 
	cout<<"请输入a"<<endl; 
	cin>>a; 
	cout<<"请输入b"<<endl; 
	cin>>b; 
	cout<<"请输入c"<<endl; 
	cin>>c; 
	d=b*b-4*a*c;
	if(d>=0){
		cout<<"实根1是："<<(-b+sqrt(d))/2/a<<endl;
		cout<<"实根2是："<<(-b-sqrt(d))/2/a<<endl;
	}
	else  cout<<"无实根";
	return 0; 
}
