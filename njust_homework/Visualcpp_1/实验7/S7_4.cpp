#include<iostream>
using namespace std;
int main(){
	int fun(int n);
	int n,mul; 
	cout<<"输入整数(输入0结束）"<<endl;
	cin>>n;
	while(n){
		mul=fun(n);
		cout<<n<<"的各个位数积为："<<mul<<endl; 
		cout<<"输入整数(输入0结束）"<<endl;
		cin>>n;
	} 
return 0;
}

int fun(int n){
	int sum=1;
	while(n){
	sum*=n%10;
	n/=10;
	}
	return sum;
}
