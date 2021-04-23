#include<iostream>
using namespace std;
int main(){
	int i,j,k;
	int colum,saddle,max,flag=0;
	int a[4][4]={{5,12,23,56},{19,28,37,46},{-12,-34,-6,8},{4,6,34,10}};
	for(i=0;i<4;i++){
		max=a[i][0];
		for(j=0;j<4;j++)
			if(max<a[i][j]){
				max=a[i][j];
				colum=j;
			}
		for(k=0;k<4;k++)
		if(max>a[k][colum]) max=a[k][colum];
		if(max==a[i][colum]){
			flag=1;saddle=max;break;
		}
		}
	if(flag) cout<<"saddle ="<<saddle<<",row = "<<i<<",colum = "<<colum<<endl;
	else cout<<"No saddle\n";
	}

