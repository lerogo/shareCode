#include<iostream>
using namespace std;
int main()
{
	double a,b,c;
	cout<<"�����������ε�����:"<<endl;
	cin>>a>>b>>c;
	if((b+c>a)&&(a+c>b)&&(a+b>c)) cout<<"Triangle\n";
	else cout<<"Not Triangle\n";
	return 0; 
}
