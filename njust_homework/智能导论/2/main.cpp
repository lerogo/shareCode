#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<time.h>
using namespace std;

int main() {
	srand(time(0));
	int n = 0x0007ffff;
	
	long long low = 0;
	for(int i=0;i<n;++i){
		double x = (rand() / double(RAND_MAX));
		double y = (rand() / double(RAND_MAX))*(exp(1));
		y < exp(x) && ++low;
	}
	cout<<double(low) / n * exp(1) <<endl;
	system("pause");
	return 0;
}
