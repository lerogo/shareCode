#include<iostream>
using namespace std;
int main(){
	
	int a,q=0;
	cout<<"������һ����������"<<endl;
	cin>>a;
	for(int i=2;i<a/2;i++)
		if(a%i==0) {q=1;break;}
	if(q==1) cout<<endl<<a<<"������"<<endl;
	else cout<<a<<"��������"<<endl;
	return 0;
}
