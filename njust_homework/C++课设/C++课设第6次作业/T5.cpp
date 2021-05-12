#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>
using namespace std;

int getLine(const char *filename){
    ifstream infile(filename,ios::in);
    if (!infile)
    {
        cout << "不能打开输入文件：" << filename<< endl;
        exit(0);
    }
    infile>>noskipws;
    int cnt=0;
    char ch;
    while(infile>>ch){
        if(ch=='\n') ++cnt;
    }
    infile.close();
    return cnt;
}

int getLineNoEmpty(const char *filename){
    ifstream infile(filename,ios::in);
    if (!infile)
    {
        cout << "不能打开输入文件：" << filename<< endl;
        exit(0);
    }
    infile>>noskipws;
    int cnt=0;
    char ch,cht;
    while(infile>>ch){
        if(ch=='\n'&&cht!='\n') ++cnt;
        cht=ch;
    }
    infile.close();
    return cnt;
}

int main()
{
    char filename[300];
    cout<<"请输入文件名："<<endl;
    cin.getline(filename,300);

    int a=getLine(filename);
    int b=getLineNoEmpty(filename);
    cout<<"所有行数："<<a<<endl;
    cout<<"含字符行数："<<b<<endl;

    return 0;
}
