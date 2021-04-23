#include<iostream>
#include<string>
using namespace std;
int main(){
    char str[100];
    cout<<"ÇëÊäÈëÒ»´®Êý×Ö×Ö·û"<<endl;
    cin.getline(str,100);
    int i=0,s=0;
    while(str[i])   s=s*10+str[i++]-'0';
    cout<<s<<endl;
    return 0;
}
