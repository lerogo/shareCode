#include<iostream>
using namespace std;
int main()
{
	char a;
	int b=0;
	cout<<"���������������������λ�κ�"<<endl; 
	while(cin.get(a))
	{	if(a=='\n') break;
		else if(a>47&&a<58)
		{	a-=48;
			b+=a;
		}
	}
	cout<<"����λ�κ�Ϊ��"<<b<<endl;
	return 0; 
}
