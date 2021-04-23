#include<iostream>
#include<cmath>
using namespace std;
double f1(double x)
{	return 1.0/(2+sin(x));	}
double f2(double x)
{	return 1.0/(2-cos(x));	}
double f3(double x)
{	return (1.0+x)/(1+x*x);	}
double integral(double(*pf)(double),int n,double a,double b){
	double h;h=(b-a)/n;
	double result;result = (pf(a)+pf(b))/2;
	for(int i=1;i<n;i++)
		result = result +pf(a+i);
	result = result*h;
	return result;
}
int main(){
	cout<<"f1(x)="<<endl;
	cout<<"n=1000:"<<integral(f1,1000,1.0,2.0)<<endl;
	cout<<"f2(x)="<<endl;
	cout<<"n=2000:"<<integral(f2,2000,2.0,3.0)<<endl;
	cout<<"f2(x)="<<endl;
	cout<<"n=3000:"<<integral(f2,3000,2.0,4.0)<<endl;
return 0;	 
}
