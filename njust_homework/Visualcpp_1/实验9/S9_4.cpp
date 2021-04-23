#include<iostream>
using namespace std;
int main(){
	int n=10;int arr[10][10];
	for(int i=0;i<n;i++){
		for(int j=0;j<i+1;j++){
			if(j==0||j==i) arr[i][j]=1; 
			else arr[i][j]=arr[i-1][j]+arr[i-1][j-1]; 
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<i+1;j++){
			cout<<arr[i][j]<<"  ";
	}
	cout<<endl;
}
return 0;	 
}
