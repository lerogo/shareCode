#include<iostream>
#include<string.h>
using namespace std;
int fun(char *p,char *q){
    int np=0,nq=0,sum=0,num=0;
    np=strlen(p);nq=strlen(q)-1;
    for(int i=0;i<np;i++){
        if(p[i]==q[sum]) {
            sum++;
            if(sum==nq) {num++;sum=0;}
        }
        else sum=0;
    }
    return num;
}
int main(){
    int n,n1;
    cout<<"������ĸ�ַ�������:"<<endl;
        cin>>n;  char *p;  p=new char[n];
    cout<<"���������ĸ�ַ�:"<<endl;
        for(int i=0;i<n;i++) cin>>p[i];
    cout<<"���������ַ�������:"<<endl;
        cin>>n1;  char *q;  q=new char[n1];
    cout<<"������������ַ�:"<<endl;
        for(int i=0;i<n1;i++) cin>>q[i];

    cout<<n1<<"  "<<strlen(q);
    int s=fun(p,q);
    cout<<s<<endl;
    return 0;
}
