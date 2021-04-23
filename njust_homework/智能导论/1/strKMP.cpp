#include<iostream>
#include<string>
using namespace std;

class strUtil {
	private:
		static void getNext(string str,int *next);					//��� KMP���� next
	public:
		static int strCmp(string str,string strt,int index = 0);	//KMPģʽƥ��
		static int getCnt(string str,string strt);
};

int main() {
	string strt = "123";
	string str = "qwe123w";
	cout<<"�������Ӵ�: " ;
	while(cin.peek()=='\n'){
		cin.get();
	}
	getline(cin,strt);
	cout<<"����������: " ;
	while(cin.peek()=='\n'){
		cin.get();
	}
	getline(cin,str);
	cout<<"������ַ����ֱ�Ϊ��"<<endl<<strt<<endl<<str<<endl<<endl;
	cout<<"��һ�γ���λ�ã�"<<strUtil::strCmp(str,strt)<<endl;
	cout<<"�����ܴ�����"<<strUtil::getCnt(str,strt)<<endl;
	
	system("pause");
	return 0;
}



int strUtil::getCnt(string str,string strt) {
	int len = strt.length(),cnt = 0,len2 = str.length();
	for(int index = strUtil::strCmp(str,strt); index!=-1 && index+len <= len2; index = strUtil::strCmp(str,strt,index+len)) {
		++cnt;
	}
	return cnt;
}

int strUtil::strCmp(string str,string strt,int index) {
	int strLen = str.length() , strtLen = strt.length();//����
	if(index>strLen) return -1;
	//��index--len������
	str.assign(str,index,strLen);
	int i = 0,j = 0; //iΪ����index  jΪ�Ӵ�����index

	//���ڻ�ȡnext
	int *next = new int [strtLen];
	strUtil::getNext(strt,next);

	while(i<strLen && j<strtLen) {
		if(j == -1 || str[i] == strt[j]) {
			//����ƥ��
			++i;
			++j;
		} else {
			//��ͬ����һ��
			j = next[j];
		}
	}
	delete next;
	if(j>=strtLen) {
		return index + i - strtLen;
	} else {
		return -1;
	}
}

void strUtil::getNext(string str,int *next) {
	int i = 0,j = -1;
	next[i] = -1;
	int len = str.length();
	while(i<len) {
		//ƥ��
		if(j==-1||str[i]==str[j]) {
			++i;
			++j;
			//��ͬ�����ǰ����ֹ�
			if(str[i]==str[j]) {
				next[i] = next[j];
			} else {
				//δ���ֹ� �µ�
				next[i] = j;
			}
		} else {
			// ����
			j = next[j];
		}
	}
}
