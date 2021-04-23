#include<iostream>
#include<string.h>
using namespace std;
int fun(char *p,int *q,int e){
    int j=1,s=0;q[0]=0;
    for(int i=0;i<e;i++){
        if(p[i]<='9'&&p[i]>='0') {q[s]=q[s]*10+p[i]-48;}
        else if(i>0&&p[i-1]<='9'&&p[i-1]>='0') {j=1;s++;q[s]=0;}
    }
    if(p[e-1]<='9'&&p[e-1]>='0') return s+1;
    else return s;
}
int main(){
    int n;
    cout<<"请输入所需字符串长度:"<<endl;
    cin>>n;
    char *p;
    p=new char[n];
    cout<<"请输入你的字符:"<<endl;
    for(int i=0;i<n;i++) cin>>p[i];
    int *q;
    q=new int[n];
    int s=fun(p,q,n);
    cout<<"数字个数为:"<<endl<<s<<endl;
    cout<<"数字分别为:"<<endl;
    for(int i=0;i<s;i++){
        cout<<q[i]<<"  ";
    }
    return 0;
}
