#include<iostream>
#include<string>
using namespace std;

class strUtil {
	private:
		static void getNext(string str,int *next);					//获得 KMP所需 next
	public:
		static int strCmp(string str,string strt,int index = 0);	//KMP模式匹配
		static int getCnt(string str,string strt);
};

int main() {
	string strt = "123";
	string str = "qwe123w";
	cout<<"请输入子串: " ;
	while(cin.peek()=='\n'){
		cin.get();
	}
	getline(cin,strt);
	cout<<"请输入主串: " ;
	while(cin.peek()=='\n'){
		cin.get();
	}
	getline(cin,str);
	cout<<"输入的字符串分别为："<<endl<<strt<<endl<<str<<endl<<endl;
	cout<<"第一次出现位置："<<strUtil::strCmp(str,strt)<<endl;
	cout<<"出现总次数："<<strUtil::getCnt(str,strt)<<endl;
	
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
	int strLen = str.length() , strtLen = strt.length();//长度
	if(index>strLen) return -1;
	//将index--len个拷贝
	str.assign(str,index,strLen);
	int i = 0,j = 0; //i为主串index  j为子串回溯index

	//用于获取next
	int *next = new int [strtLen];
	strUtil::getNext(strt,next);

	while(i<strLen && j<strtLen) {
		if(j == -1 || str[i] == strt[j]) {
			//不断匹配
			++i;
			++j;
		} else {
			//不同则下一个
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
		//匹配
		if(j==-1||str[i]==str[j]) {
			++i;
			++j;
			//相同则表明前面出现过
			if(str[i]==str[j]) {
				next[i] = next[j];
			} else {
				//未出现过 新的
				next[i] = j;
			}
		} else {
			// 回溯
			j = next[j];
		}
	}
}
