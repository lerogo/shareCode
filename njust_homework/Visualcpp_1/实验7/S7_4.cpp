#include<iostream>
using namespace std;
int main(){
	int fun(int n);
	int n,mul; 
	cout<<"��������(����0������"<<endl;
	cin>>n;
	while(n){
		mul=fun(n);
		cout<<n<<"�ĸ���λ����Ϊ��"<<mul<<endl; 
		cout<<"��������(����0������"<<endl;
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
