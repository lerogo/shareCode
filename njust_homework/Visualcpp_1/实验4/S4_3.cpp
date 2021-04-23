#include<iostream>
using namespace std;
int main(){
	
	int a,q=0;
	cout<<"请输入一个正整数："<<endl;
	cin>>a;
	for(int i=2;i<a/2;i++)
		if(a%i==0) {q=1;break;}
	if(q==1) cout<<endl<<a<<"是素数"<<endl;
	else cout<<a<<"不是素数"<<endl;
	return 0;
}
