#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string>
using namespace std;

const string ways[4] = {"����","����","����","����"};

int main() {
	srand(time(0));
	int s = 50 - 1;
	for(int i=0; i<3; ++i) { 
		//���һ�� �ұ�һ�� ��������һ��Ϊ0����Ȼ�ұ�Ϊ0��0-1=-1�� 
		int left = (rand()%(s-1)) + 1 , right = s - left - 1;
		//�������� 
		int t_l = left%4 , t_r = right%4;
		//����Ƿ�������0���еĻ�����Ϊ4 �� s -= 4
		t_l || (s -= 4);
		t_r || (s -= 4);
		//���¼���s s-=1 ��Ϊ�ұ��ó�1
		s -= t_l + t_r + 1;
	}
	/*
	 *������ ���s��4����� 36��32��28��24
	 *����4������ֱ����4�����õ��̷ֱ���9��8��7��6
	 *9Ϊ����������Ϊ3/16����6Ϊ����������Ϊ1/16��
	 *7Ϊ����������Ϊ5/16����8Ϊ����������Ϊ7/16��
	 */ 
	
	cout<<ways[(s/4-6)]<<endl;
	system("pause");
	return 0;
}





