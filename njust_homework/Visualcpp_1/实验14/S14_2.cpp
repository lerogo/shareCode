#include<iostream>
#include<string.h>
using namespace std;
char fun1(char *s,int n, int r){
    int i=0,t;
    while(n){
        t=n%r;
        if(t>=10) s[i++]=t-10+'A';
        else s[i++]=t+48;
        n=n/r;
    }
    s[i]='\0';
}
char fun2(char *s){
    char ch;
    int len=strlen(s);
    for(int i=0;i<len;i++){
        ch=s[i];
        s[i]=s[len-i-1];
        s[len-i-1]=ch;
    }
}
int main(){
    char s[200];
    int n,r;
    cout<<"输入你想转换的十进制数："<<endl;
    cin>>n;
    cout<<"输入你想将"<<n<<"转换成多少进制"<<endl;
    cin>>r;
    fun1(s,n,r);fun2(s);
    cout<<s;
    return 0;
}
