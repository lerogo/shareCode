#include <iostream>
#include <string>
#include <time.h>
using namespace std;
typedef long long LL;

const int MAX_STEP = 0xffff;		//����� 
const int MAX_CAP = 0x7fffffff;		//���ֵ 
const string way[6] = {"a-->b",	"b-->a","a-->c","c-->a","b-->c","c-->b"};		//�ƶ����� 
int step[MAX_STEP][4];		//step[i][0/1/2] �ֱ����Ŀǰƿ������ step[i][3] ������һ������
struct {					//�������ٵ� һ�� ����
	int len = MAX_CAP;
	int step[MAX_STEP][4];
} minStep;
int b1,b2,b3,target;		// ����ƿ������  Ŀ��

bool isRight(int index);	//�жϵ�x���Ƿ���ȷ �ﵽtarget
bool isCircle(int index);	//�жϵ� index ���Ƿ���֮ǰ�ظ�
void move(int index);		//�Ե�index���Ľ��м��� ͨ��step[index-1];
void show(int step[][4],int index,int cnt);		//��ʾ 
void getAns(int index,int &cnt);				//�ݹ�ʵ�� 

int main() {
	cout<<"��������ƿ������(-1��������)��Ŀ��: ";
	cin>>b1>>b2>>b3>>target;

	b1==-1&&(b1=MAX_CAP);
	b2==-1&&(b2=MAX_CAP);
	b3==-1&&(b3=MAX_CAP);

	cout<<"��������ƿ�ӳ�ʼֵ: ";
	cin>>step[0][0]>>step[0][1]>>step[0][2];
	
	clock_t start, finish; 
	start = clock();   
	int index = 0,cnt = 0;
	if (isRight(index)) {
		++cnt;
		show(step,index,cnt);
		return 0;
	}
	getAns(index,cnt);		//�ݹ�ʵ��
	if(cnt==0){
		cout<<"�޽�"<<endl;
		return 0;
	}
	show(minStep.step,minStep.len,-1);
	finish = clock();  
	cout<<endl<<"������ʱ" <<(double)(finish - start) / CLOCKS_PER_SEC;
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
		cout<<"�������ٵ�һ�֣�"<<endl;
	} else {
		cout<<"�� "<<cnt<<" ��"<<endl;
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
	cout<<"����Ϊ��"<< index<<endl<<endl;
}

//�жϵ� index ���Ƿ���֮ǰ�ظ�
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

//�жϵ�x���Ƿ���ȷ �ﵽtarget
bool isRight(int index) {
	for(int i=0; i<3; ++i) {
		if(step[index][i]==target) return true;
	}
	return false;
}


void move(int index) {	//�Ե�index���Ľ��м��� ͨ��step[index-1];
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

