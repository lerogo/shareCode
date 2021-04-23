#include<iostream>
using namespace std;
int fun(int *w,int p,int n){
		int t,i,j;
		for(i=0;i<=p;i++){
			t=*w;
			for(j=0;j<n-1;j++){
				*(w+j)=*(w+j+1);}
			*(w+j)=t;
		}
	}
int main(){
	int a[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	int p;cout<<"Inpot p:"<<" ";cin>>p;
	int n=sizeof(a)/sizeof(a[0]);
	fun(a,p,n);
	for(int i=0;i<n;i++)
		cout<<a[i]<<"\t";
	cout<<endl;
return 0;	 
}
