#include <iostream>
#include <string>
#include <time.h>
using namespace std;
typedef long long LL;

const int MAX_STEP = 0xffff;		//最大步数 
const int MAX_CAP = 0x7fffffff;		//最大值 
const string way[6] = {"a-->b",	"b-->a","a-->c","c-->a","b-->c","c-->b"};		//移动步骤 
int step[MAX_STEP][4];		//step[i][0/1/2] 分别代表目前瓶子容量 step[i][3] 代表下一步操作
struct {					//保存最少的 一种 做法
	int len = MAX_CAP;
	int step[MAX_STEP][4];
} minStep;
int b1,b2,b3,target;		// 三个瓶子容量  目标

bool isRight(int index);	//判断第x步是否正确 达到target
bool isCircle(int index);	//判断第 index 步是否与之前重复
void move(int index);		//对第index个的进行计算 通过step[index-1];
void show(int step[][4],int index,int cnt);		//显示 
void getAns(int index,int &cnt);				//递归实现 

int main() {
	cout<<"输入三个瓶子容量(-1代表无限)和目标: ";
	cin>>b1>>b2>>b3>>target;

	b1==-1&&(b1=MAX_CAP);
	b2==-1&&(b2=MAX_CAP);
	b3==-1&&(b3=MAX_CAP);

	cout<<"输入三个瓶子初始值: ";
	cin>>step[0][0]>>step[0][1]>>step[0][2];
	
	clock_t start, finish; 
	start = clock();   
	int index = 0,cnt = 0;
	if (isRight(index)) {
		++cnt;
		show(step,index,cnt);
		return 0;
	}
	getAns(index,cnt);		//递归实现
	if(cnt==0){
		cout<<"无解"<<endl;
		return 0;
	}
	show(minStep.step,minStep.len,-1);
	finish = clock();  
	cout<<endl<<"程序用时" <<(double)(finish - start) / CLOCKS_PER_SEC;
	return 0;
}



void getAns(int index,int &cnt) {
	if(index>MAX_STEP) return;
	for(int i=0; i<6; ++i) {
		step[index][3] = i;
		move(index+1);
		if(isRight(index+1)) {
			++cnt;
			show(step,index+1,cnt);
		} else if(!isCircle(index+1)) {
			getAns(index+1,cnt);
		}
	}

}

void show(int step[][4],int index,int cnt) {
	if(cnt==-1) {
		cout<<"步数最少的一种："<<endl;
	} else {
		cout<<"第 "<<cnt<<" 种"<<endl;
	}
	cout<<"a -- b -- c"<<endl;
	if (minStep.len>index) {
		minStep.len = index;
		for(int i=0; i<=index; ++i) {
			for(int j=0; j<4; ++j) {
				minStep.step[i][j] = step[i][j];
			}
		}
	}
	for(int i=0; i<index; ++i) {
		cout<<step[i][0]<<"--"<<step[i][1]<<"--"<<step[i][2];
		cout<<"    "<<way[step[i][3]]<<endl;
	}
	cout<<step[index][0]<<"--"<<step[index][1]<<"--"<<step[index][2]<<endl;
	cout<<"步数为："<< index<<endl<<endl;
}

//判断第 index 步是否与之前重复
bool isCircle(int index) {
	bool flag = false;
	for(int i = index-1; i>=0; --i) {
		flag = false;
		for(int j=0; j<3; ++j) {
			if(step[i][j] != step[index][j]) {
				flag = true;
				break;
			}
		}
		if (!flag) return true;
	}
	return false;
}

//判断第x步是否正确 达到target
bool isRight(int index) {
	for(int i=0; i<3; ++i) {
		if(step[index][i]==target) return true;
	}
	return false;
}


void move(int index) {	//对第index个的进行计算 通过step[index-1];
	int lastIndex = index - 1;
	//"a-->b","b-->a","a-->c","c-->a","b-->c","c-->b"
	//0 -- a
	//1 -- b
	//2 -- c
	switch(step[lastIndex][3]) {
		case 0:
			step[index][1] = step[lastIndex][0] + step[lastIndex][1];
			if (step[index][1]>b2) step[index][1] = b2;
			step[index][0] = step[lastIndex][0] - step[index][1] + step[lastIndex][1];
			step[index][2] = step[lastIndex][2];
			break;
		case 1:
			step[index][0] = step[lastIndex][0] + step[lastIndex][1];
			if (step[index][0]>b1) step[index][0] = b1;
			step[index][1] = step[lastIndex][0] - step[index][0] + step[lastIndex][1];
			step[index][2] = step[lastIndex][2];
			break;
		case 2:
			step[index][2] = step[lastIndex][0] + step[lastIndex][2];
			if (step[index][2]>b3) step[index][2] = b3;
			step[index][0] = step[lastIndex][0] - step[index][2] + step[lastIndex][2];
			step[index][1] = step[lastIndex][1];
			break;
		case 3:
			step[index][0] = step[lastIndex][0] + step[lastIndex][2];
			if (step[index][0]>b1) step[index][0] = b1;
			step[index][2] = step[lastIndex][0] - step[index][0] + step[lastIndex][2];
			step[index][1] = step[lastIndex][1];
			break;
		case 4:
			step[index][2] = step[lastIndex][1] + step[lastIndex][2];
			if (step[index][2]>b3) step[index][2] = b3;
			step[index][1] = step[lastIndex][1] - step[index][2] + step[lastIndex][2];
			step[index][0] = step[lastIndex][0];
			break;
		case 5:
			step[index][1] = step[lastIndex][1] + step[lastIndex][2];
			if (step[index][1]>b2) step[index][1] = b2;
			step[index][2] = step[lastIndex][1] - step[index][1] + step[lastIndex][2];
			step[index][0] = step[lastIndex][0];
			break;
	}
}

