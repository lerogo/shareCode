#include<iostream>
using namespace std;
int main(){
	int a,b,c;
	cout<<"Input three number��"<<endl;
	cin>>a>>b>>c;
	for(int i=a;i<=a*b*c;i++)				//����С������ 
	if(i%a==0&&i%b==0&&i%c==0)
	{
		cout								//����cout���
			<<a<<"  "<<b<<"  "<<c
			<<"  ����С��������"<<endl
			<<i<<endl;
		break;
	}
	return 0;
}
