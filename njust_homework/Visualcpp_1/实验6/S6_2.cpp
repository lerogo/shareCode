//牛顿切线法求一元二次函数一个解 
#include<iostream>
using namespace std;
float f(float x){
	float y;
	y=x*x+3*x-4;
	return y;
}
double df(float x){
	float y;
	y=2*x+3;
	return y;
}
int main(){
	float x1=0;
	do{
		x1=x1-f(x1)/df(x1);
	}while(f(x1)>1e-5||f(x1)<(-1e-5));
	cout<<"x1="<<x1<<endl;
	return 0;
}
