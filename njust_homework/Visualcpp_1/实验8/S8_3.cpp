#include<iostream>
using namespace std;
int main(){
	int a[]={2,5,78,4,6,3,89,12,15,34};
	int j,max,t;
		max=0;
		for(int j=0;j<10;j++)
			if(a[j]>a[max]) max=j;
		cout<<"max = "<<" "<<a[max]<<","
		<<"maxindex = "<<max+1<<endl;
		return 0;
}