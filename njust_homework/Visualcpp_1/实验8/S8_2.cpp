#include<iostream>
using namespace std;
int main(){
	int a[]={9,8,7,6,5,4};
	int i,j,min,t;
	int n=6;
	for(int i=0;i<n-1;i++){
		min=i;
		for(int j=i;j<n;j++)
			if(a[j]<a[min]) min=j;
			t=a[min];a[min]=a[i];a[i]=t;
		
	}
	for(i=0;i<n;i++) cout<<a[i]<<"\t";
	cout<<endl;
	return 0;
}