#include<iostream>
using namespace std;
int main()
{
	int n,t=1,y=1;
	cout<<"Input n"<<endl;
	cin>>n;
	for(int i=2;i<=n;i++){
		t*=i;
		y+=t; 
	}
	cout<<"1!+2!+...+n!="<<y<<endl;
	return 0; 
}

