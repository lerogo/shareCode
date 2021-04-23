#include<iostream>
using namespace std;
int main()
{
	double y,q,x;
	cout<<"Input x"<<endl;
	cin>>x;
	y=x;
	do{
		q=y;
		y=2.0/3.0*q+x/3.0/q/q;
	}
	while(-(1e-5)>=y-q||y-q>=(1e-5));
	cout<<"3¡Ì"<<x<<"="<<y<<endl;
	return 0; 
}

