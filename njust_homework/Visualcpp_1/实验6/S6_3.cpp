//二分法求一元二次函数一个解
#include<iostream>
#include<math.h>
using namespace std;
float f(float x){
	return x*x+3*x-4;
}
int main(){
	float x1,x2,x0;
	do{
		cout<<"请输入初值x1和x2："<<endl;
		cin>>x1>>x2;
	} while(f(x1)*f(x2)>0);
	do{
		x0=(x1+x2)/2;
		if(f(x0)*f(x1)>0) x1=x0;
		else x2=x0;
	}while(fabs(f(x0))>1e-5);
	cout<<"x0="<<x0<<endl;
	return 0;
}
