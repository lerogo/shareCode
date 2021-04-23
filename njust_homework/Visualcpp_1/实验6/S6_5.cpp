//牛顿递归求一元二次函数一个解 
#include<iostream>
using namespace std;
float f(float x){
	float y;
	y=x*x+3.0*x-4.0;
	return y;
}
float df(float x){
	float y;
	y=2.0*x+3.0;
	return y;
}
float dg(float x1){
	float x0;
	x0=x1;
	if(f(x1)>(1e-5)||f(x1)<(-1e-5)) x1=dg(x1);
	x1=x0-f(x0)/df(x0);
	
	return x1;
}
int main(){
	cout<<"x1="<<dg(0.0)<<endl;
	return 0;
}
