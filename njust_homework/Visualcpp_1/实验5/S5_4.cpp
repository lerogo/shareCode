#include<iostream>
using namespace std;
int main()
{
	double x=2.5,x1,x2,y=0;
	int n; cout<<"Input n"<<endl; cin>>n;
	for(int i=1;i<2*n;i+=2){		//遍历n项 
		x1=1.0;x=2.5;x2=2.5;		//数据赋值 
		for(int j=1;j<=i;j++){		//计算阶乘 
			x1*=j;
		}
		for(int j=1;j<i;j++) x2*=x; //计算次方 
		if((i/2+1)%2==0) y-=x2/x1;	//奇偶不同号 
		else y+=x2/x1;
	}
	cout<<y;						//输出最后值 
	return 0; 
}

