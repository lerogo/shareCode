#include<iostream>
using namespace std;
int main()
{
	char a;
	int b=0;
	cout<<"请输入任意整数以求各个位次和"<<endl; 
	while(cin.get(a))
	{	if(a=='\n') break;
		else if(a>47&&a<58)
		{	a-=48;
			b+=a;
		}
	}
	cout<<"各个位次和为："<<b<<endl;
	return 0; 
}
