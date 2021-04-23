#include<iostream>
using namespace std;
float fun(float x){
	float y;
	y=2*x*x+5*x+3;
	return y;
}
int main(){
	float y1,y2;
	y1=fun(1.0);
	y2=fun(1.2);
	cout<<"y1="<<y1<<endl;
	cout<<"y2="<<y2<<endl;
	return 0;
}
