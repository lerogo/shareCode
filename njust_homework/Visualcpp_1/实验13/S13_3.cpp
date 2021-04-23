#include<iostream>
#include<cmath>
using namespace std;
//求平均值 
double Average(int *p,double n){
	double sum=0.0;
	for(int i=0;i<n;i++){
		sum+=p[i];
	}
	return sum/n;
} 
//给数组赋值 
int GiveArr(int *p,int n){
	for(int i=1;i<n;i++)
		p[i]=(15*p[i-1]+97)%256;
}
//找到所需值数组的值 
int FindMax(int *p,int n,int Average){
	int Max=fabs(p[0]-Average);
	int num=p[0];
	for(int i=0;i<n;i++)
		if(fabs(p[i]-Average)>Max){
			Max=fabs(p[i]-Average);
			num=p[i];
	}
	return num; 
}
//删除数组中找到的值 
int del(int *p,int n,int num){
	for(int i=0;i<n;i++){
		if(p[i]==num){
			for(int j=i;j<n;j++){
				p[j]=p[j+1];
			}
		break;
		}
	}
}
int main(){
	const int n=16;
	int a[n];
	a[0]=55;
	GiveArr(a,n);
	cout<<"原来数组是："<<endl; 
	for(int i=0;i<n;i++) cout<<a[i]<<"  ";
	cout<<endl;
	double Ave=Average(a,n);
	cout<<"Average = "<<Ave<<endl;
	int Max=FindMax(a,n,Ave);
	cout<<"Max = "<<Max<<endl;
	del(a,n,Max);
	cout<<"数组删除"<<Max<<"后是："<<endl;
	for(int i=0;i<n-1;i++) cout<<a[i]<<"  ";
return 0;	 
}
