#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<math.h>
using namespace std;
int main()
{
	double x;
	int n;
	fstream fio("fsqrt.dat",ios::in|ios::out|ios::binary);
	if(!fio)
	{
		cout<<"File Operator Error!\n";
		exit(0);
	}
	for(int i=1;i<101;i++)
	{
		x=sqrt(i);
		fio.write((char *)&x,sizeof(x));
	}
	cout<<"请输入一个1~100之间的整数:(输入0结束)"<<endl;
	cin>>n;
	while(1)
	{
		if(n==0)
		{
			cout<<"程序结束.\n";
			exit(0);
		}
		while(n<1||n>100)
		{
			cout<<"输入的数据错误,请重新输入:\n";
			cin>>n;
			if(n==0)
			{
				cout<<"程序结束.\n";
				exit(0);
			}
		}
		n=n-1;
		fio.seekg(n*sizeof(double),ios::beg);
		fio.read((char *)&x,sizeof(double));
		cout<<n+1<<"的平方根是:"<<x<<endl;
		cout<<"请输入一个1~100之间的整数:(输入0结束)"<<endl;
		cin>>n;
	}
	fio.close();
	return 0;
}

