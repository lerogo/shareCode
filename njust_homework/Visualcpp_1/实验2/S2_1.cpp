#include<iostream>
using namespace std;
int main()
{
	double a,b,c;
	cout<<"请输入三角形的三边:"<<endl;
	cin>>a>>b>>c;
	if((b+c>a)&&(a+c>b)&&(a+b>c)) cout<<"Triangle\n";
	else cout<<"Not Triangle\n";
	return 0; 
}
