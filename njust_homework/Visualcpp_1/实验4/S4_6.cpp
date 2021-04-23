#include<iostream>
using namespace std;
int main(){
	int q=0;
	//"完数"的算法，输出"完数"
	for(int i=2;i<=1000;i++){
		for(int j=1;j<=i/2;j++){
			if(i%j==0) q+=j;
		}
		if(q==i) cout<<i<<endl;
		q=0;
	}
	return 0;
}
