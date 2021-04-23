#include<iostream>
using namespace std;
//平均值 
double Average(int *p,int h,int l){
	double sum=0;
	for(int i=0;i<h*l;i++){
		sum+=*(p+i);
	}
	return sum/h/l;
}
//找最大 
int FindMax(int (*p)[4],int n){
	int max=**p;
	for(int i=0;i<n;i++){
		for(int j=0;j<4;j++){
			if(max<*(*(p+i)+j))
				max=*(*(p+i)+j);
		}
	}
	return max;
}
//找最小 
int FindMin(int (*p)[4],int n){
	int min=**p;
	for(int i=0;i<n;i++){
		for(int j=0;j<4;j++){
			if(min>*(*(p+i)+j))
				min=*(*(p+i)+j);
		}
	}
	return min;
}
int main(){
	int a[3][4]={{2,3,4,5},{12,13,14,15},{1,2,3,4}};
	double Ave = Average(a[0],3,4);
	cout<<"Average = "<<Ave<<endl;
	int Max = FindMax(a,3);
	cout<<"Max = "<<Max<<endl;
	int Min = FindMin(a,3);
	cout<<"Min = "<<Min<<endl;
	return 0;	 
}
