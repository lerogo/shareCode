/*----9181040G0818�ƺ���----��4������ͼ��Ч��----9181040G0818�ƺ���----*/

#include<stdlib.h>						//exit()
#include<iostream>						//���������
#include<Windows.h>						//�쳣�Զ��˳�ʱ��
#include"XinXi.h"
#include"ShiXian.h"
using namespace std;

//����������
int Match(int nRed, int nGreen, int nBlue);						//Ѱ��������ƥ��ĵ�ɫ������
int Smooth(ifstream& infile, ofstream& outfile);				//�ữЧ��
int Sharp(ifstream& infile, ofstream& outfile);					//�񻯴���
int Emboss(ifstream& infile, ofstream& outfile);				//����Ч��
int Spread(ifstream& infile, ofstream& outfile);				//��ɢЧ��
int Masec(ifstream& infile, ofstream& outfile);					//������Ч��
int Initial(char nChoice);										//��ʼ��ͼ���ļ�

//��ʾѡ��
void show() {
	cout << "��ѡ��: " << endl;
	cout << "\n\t1. �ữ" << endl;
	cout << "\n\t2. ��" << endl;
	cout << "\n\t3. ����" << endl;
	cout << "\n\t4. ��ɢ" << endl;
	cout << "\n\t5. ������" << endl;
	cout << "\n\t6. �˳�" << endl;
}

//��������в���
int set(char nChoice[]) {
	if ('0' < nChoice[0] && nChoice[0] < '6' && !nChoice[1]) {
		if (Initial(nChoice[0]))
			cout << endl << "�������!" << endl << endl;
		else
			cout << endl << "����������ʧ��!" << endl << endl;
	}
	else if (nChoice[0] == '6' && !nChoice[1]) {
		cout << "ѡ���˳�,3S���Զ��˳�!" << endl;
		Sleep(3000);
		exit(1);
	}
	else {
		cout << "����������������룡" << endl;
	}
}

int main() {
	while (1) {
		char nChoice[100];					//ʹ���ַ�����������������³������������
		show();								//��ʾѡ��
		cin >> nChoice;						//����ѡ��
		set(nChoice);						//����
	}
	return 0;
}
