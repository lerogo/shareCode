#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string>
using namespace std;

const string ways[4] = {"老阴","少阳","少阴","老阳"};

int main() {
	srand(time(0));
	int s = 50 - 1;
	for(int i=0; i<3; ++i) { 
		//左边一堆 右边一堆 （避免有一边为0，不然右边为0，0-1=-1） 
		int left = (rand()%(s-1)) + 1 , right = s - left - 1;
		//计算余数 
		int t_l = left%4 , t_r = right%4;
		//检测是否有余数0，有的话令其为4 则 s -= 4
		t_l || (s -= 4);
		t_r || (s -= 4);
		//重新计算s s-=1 因为右边拿出1
		s -= t_l + t_r + 1;
	}
	/*
	 *分析后 最后s有4种情况 36、32、28或24
	 *将这4个结果分别除以4，所得的商分别是9、8、7、6
	 *9为老阳（概率为3/16），6为老阴（概率为1/16）
	 *7为少阳（概率为5/16），8为少阴（概率为7/16）
	 */ 
	
	cout<<ways[(s/4-6)]<<endl;
	system("pause");
	return 0;
}





