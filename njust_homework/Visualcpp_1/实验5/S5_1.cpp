#include<iostream>
using namespace std;
int main()
{
	int t=2,s=0;
	for(int i=0;i<7;i++){
		s+=t;
		t=t*10+2;
	} 
	cout<<"2+22+...+2222222="<<s<<endl;
	return 0; 
}

