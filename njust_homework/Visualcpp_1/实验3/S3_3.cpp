#include<iostream>
using namespace std;
int main()
{
	int a0,a1,a2,b;
	for(b=100;b<=999;b++){
		a2=b/100;
		a1=b/10%10;
		a0=b%10;
		if(b==a0*a0*a0+a1*a1*a1+a2*a2*a2)
		cout<<b<<'\t'; 
	}
	cout<<endl;
	return 0; 
}
