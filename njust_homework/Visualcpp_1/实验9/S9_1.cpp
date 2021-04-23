#include<iostream>
using namespace std;
int main(){
	int i,j,row = 0,colum = 0,max;
	int a[4][4]={{5,12,23,56},{19,28,37,46},{-12,-34,6,8},{4,6,34,1}};
	max = a[0][0];
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(a[i][j]>max){
				max=a[i][j];
				row=i;
				colum=j;
			}
		}
	}
	cout<<"max = "<<max<<",row = "<<row<<",colum = "<<colum<<endl;
		return 0;
}