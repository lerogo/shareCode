#include<iostream>
using namespace std;
int main(){
	int a,b,c;
	cout<<"Input three number："<<endl;
	cin>>a>>b>>c;
	for(int i=a;i<=a*b*c;i++)				//求最小公倍数 
	if(i%a==0&&i%b==0&&i%c==0)
	{
		cout								//个人cout风格
			<<a<<"  "<<b<<"  "<<c
			<<"  的最小公倍数："<<endl
			<<i<<endl;
		break;
	}
	return 0;
}
