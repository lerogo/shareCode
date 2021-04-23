#include<iostream>
#include<fstream>
using namespace std;
int main(){
    fstream inf("str.txt",ios::in);
    fstream outf("strout.txt",ios::out);
    char string [100][30];
    int i=0;
    while(1){
        if(inf.getline(string[i++],30)!=0) continue;
        break;
    }
    outf<<"字符串个数："<<i-1<<endl;
    outf<<"字符串分别为："<<endl;
    for(int j=0;j<i-1;j++) outf<<string[j]<<endl;
    cout<<"请查看文件"<<endl;
    return 0;
}
