#include<iostream>
using namespace std;
int prime(int n){
	for(int i=2;i<n/2;i++){
		if(n%i==0) return 0;
	}
	return 1;
}
int main(){
	while(1){
		int a;cin>>a;
		if(a%2==0&&a>=6){
		for(int x1=2,xn=a-2;x1<=xn;x1++,xn--){
	    	if(prime(x1)&&prime(xn)&&x1<=xn) cout<<a<<"="<<x1<<"+"<<xn<<endl;
	    	}
		}
		else cout<<"你输出的数字不符合规范！"<<endl;
		}
return 0;
}

