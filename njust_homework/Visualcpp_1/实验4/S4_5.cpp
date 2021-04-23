#include<iostream>
using namespace std;
int main(){
	for(int i=101;i<200;i+=2){
		for(int j=3;j<i/2;j+=2){
			if(i%j==0) break;
			if(j>i/2-2) {
				cout<<i<<endl;break;}
		}
	}
	return 0;
}
