#include<iostream>
using namespace std;
int main(){
	int arr[99];
	for(int i=2;i<101;i++) arr[i-2]=i;
	for(int i=2;i<101;i++){
		for(int j=i+1;j<101;j++){
			if(arr[i-2]==0) break;
			if(arr[j-2]%arr[i-2]==0) arr[j-2]=0;
		}
	}
	for(int i=2;i<101;i++){
		if(arr[i-2]!=0) cout<<arr[i-2]<<"  ";
	}
		return 0;
}