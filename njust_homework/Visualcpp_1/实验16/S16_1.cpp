#include<iostream>
using namespace std;
//类
class Complex{
private:
    double real;                                         //函数实部
    double image;                                        //函数虚部
public:
    Complex(){}                                          //构造函数
    Complex(double re,double im){real=re;image=im;}
    Complex operator + (Complex &);                      //将“+”作为运算符重载的成员函数
    friend Complex operator - (Complex &,Complex &);     //将“-”作为运算符重载的友元函数
    //Complex operator += (Complex &);                     //将“+=”作为运算符重载的成员函数
    friend Complex operator * (Complex &,Complex &);     //将“*”作为运算符重载的友元函数
    friend istream& operator >> (istream&,Complex &);    //将输入运算符“>>”重载为友元函数
    friend ostream& operator << (ostream&,Complex &);    //将输出运算符“<<”重载为友元函数
};
//函数
Complex Complex::operator + (Complex &c){                //重载“+”的实现
    Complex cc;
    cc.real=real+c.real;
    cc.image=image+c.image;
    return cc;
}
/*Complex Complex::operator += (Complex &c){                //重载“+=”的实现
    real = real + c.real;
    image = image + c.image;
    return *this;
}
*/
Complex operator - (Complex &c1,Complex &c2){                //重载“-”作为友元函数的实现
    Complex cc;
    cc.real=c1.real-c2.real;
    cc.image=c1.image-c2.image;
    return cc;
}
Complex operator * (Complex &c1,Complex &c2){                //重载“*”作为友元函数的实现

    Complex cc;
    cc.real=c1.real*c2.real-c1.image*c2.image;
    cc.image=c1.real*c2.image+c1.image*c2.real;
    return cc;
}
istream& operator >>(istream&is,Complex &c){
    cout<<"请输入复数的实部:   ";
    is>>c.real;
    cout<<"请输入复数的虚部:   ";
    is>>c.image;
    return is;
}
ostream& operator << (ostream&os,Complex &c){
    if(c.image>1e-5)
        os<<c.real<<" + "<<c.image<<"i"<<endl;
    else if(c.image<-1e-5)
        os<<c.real<<" - "<<(-c.image)<<"i"<<endl;
    else
        os<<c.real<<endl;
    return os;
}
int main(){
    Complex c1(1,2),c2(3,4),c3;
    c3=c1+c2;
    cout<<"c1="<<c1;
    cout<<"c2="<<c2;
    cout<<"c1+c2="<<c3;
    c3=c1-c2;
    cout<<"c1-c2="<<c3;
    c3=c1*c2;
    cout<<"c1*c2="<<c3;
    /*c1 += c2 += c2;
    cout<<"c1+=c2+=c2:"<<c1<<endl;
    */
    //
    cin>>c1>>c2;
    c3=c1+c2;
    cout<<"c1="<<c1;
    cout<<"c2="<<c2;
    cout<<"c1+c2="<<c3;
    c3=c1-c2;
    cout<<"c1-c2="<<c3;
    c3=c1*c2;
    cout<<"c1*c2="<<c3;
    /*c1 += c2 += c2;
    cout<<"c1+=c2+=c2:"<<c1<<endl;
    */
    return 0;
}
