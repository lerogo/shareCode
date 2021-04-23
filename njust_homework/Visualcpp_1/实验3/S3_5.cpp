#include<iostream>
using namespace std;
int main()
{
	int a,b,c,sum=0;
	for (int i=1;i<600;i++){
		a=i/100;
		b=i/10%10;
		c=i%10;
		if(i%3==0&&(a==5||b==5||c==5)){
		cout<<i<<endl;
		sum++;
	}
	}
	cout<<sum<<endl;
	return 0; 
}
