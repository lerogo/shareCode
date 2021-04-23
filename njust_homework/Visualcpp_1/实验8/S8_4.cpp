#include<iostream>
using namespace std;
int main(){
	int a[]={9,2,5,78,4,6,3,89,12,15,34};
	int i,j,t;
	int n=11;
	//下面进行交换
	for(i=0,j=n-1;i<n/2;i++,j--) t=a[i];a[i]=a[j];a[j]=t;
	for(int i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
		return 0;
}