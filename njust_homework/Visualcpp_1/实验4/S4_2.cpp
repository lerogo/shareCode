#include<iostream>
using namespace std;
int main(){
	int a,b,c;
	cout<<"Input three number��";
	cin>>a>>b>>c;
	for(int i=a;i>0;i--){
		if(a%i==0&&b%i==0&&c%i==0){
			cout<<"���Լ���ǣ�"<<i;
			break;
		}
	}
	return 0;
}
