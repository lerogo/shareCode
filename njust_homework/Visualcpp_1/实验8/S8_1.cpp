#include<iostream>
using namespace std;
int main(){
	int a[]={9,8,7,6,5,4};
	int i,j,t;
	int n=6;
	for(i=0;i<n-1;i++){
		for(j=0;j<n-1-i;j++){
			if(a[j]>a[j+1]){
				t=a[j];a[j]=a[j+1];a[j+1]=t;
			}
		}
	}
	for(i=0;i<n;i++) cout<<a[i]<<"\t";
	cout<<endl;
	return 0;
}