#include<iostream>
using namespace std;
int main()
{
	double x=2.5,x1,x2,y=0;
	int n; cout<<"Input n"<<endl; cin>>n;
	for(int i=1;i<2*n;i+=2){		//����n�� 
		x1=1.0;x=2.5;x2=2.5;		//���ݸ�ֵ 
		for(int j=1;j<=i;j++){		//����׳� 
			x1*=j;
		}
		for(int j=1;j<i;j++) x2*=x; //����η� 
		if((i/2+1)%2==0) y-=x2/x1;	//��ż��ͬ�� 
		else y+=x2/x1;
	}
	cout<<y;						//������ֵ 
	return 0; 
}

