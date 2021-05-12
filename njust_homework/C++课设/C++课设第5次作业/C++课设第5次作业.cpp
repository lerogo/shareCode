#include<stdlib.h>
#include<iostream>
using namespace std;
//求最大公约数
int gcd(int a,int b)
{
    if(b)
    {
        return a%b==0?b:gcd(b,a%b);
    }
    return a;
}

//每次更新 使得分母大于0
void change(int &a,int &b)
{
    if(b<0)
    {
        a=-a;
        b=-b;
    }
}
class Fraction
{
    int son,mom;
public:
    //构造函数
    Fraction()
    {
        son=0;
        mom=0;
    }
    //分子  分母
    Fraction(int molecule,int denominator)
    {
        if(denominator==0)
        {
            cerr<<"Error in the calculation process"<<endl;
            exit(0);
        }
        change(molecule,denominator);
        int gcdd=gcd(molecule,denominator);
        son = molecule/gcdd;
        mom = denominator/gcdd;
        change(son,mom);
    }

    friend ostream & operator << (ostream & os,const Fraction &a)
    {
        if(a.mom==0)
        {
            os<<a.son<<"/"<<a.mom;
            return os;
        }
        int t=gcd(a.mom,a.son);
        int t1=a.son/t;
        int t2=a.mom/t;
        change(t1,t2);
        os<<t1<<"/"<<t2;
        return os;
    }

    Fraction operator +(const Fraction &a)
    {
        int t1 = this->son*a.mom+a.son*this->mom;//分子
        int t2 = this->mom * a.mom;//分母
        change(t1,t2);
        return Fraction( t1, t2 );

    }
    Fraction operator -(const Fraction &a)
    {
        int t1 = this->son*a.mom - a.son*this->mom;
        int t2 =this->mom * a.mom;
        change(t1,t2);
        return Fraction( t1, t2 );
    }
    Fraction operator * (const Fraction &a)
    {
        int t1=this->son*a.son;
        int t2=this->mom*a.mom;
        change(t1,t2);
        return Fraction( t1, t2 );
    }
    Fraction operator / (const Fraction &a)
    {
        int t1=this->son*a.mom;
        int t2=this->mom*a.son;
        change(t1,t2);
        return Fraction( t1, t2 );
    }

    friend bool operator < (const Fraction &a,const Fraction &b)
    {
        return 1.0*a.son/a.mom < 1.0*b.son/b.mom;
    }
    friend bool operator <= (const Fraction &a,const Fraction &b)
    {
        return 1.0*a.son/a.mom <= 1.0*b.son/b.mom;
    }
    friend bool operator > (const Fraction &a,const Fraction &b)
    {
        return 1.0*a.son/a.mom > 1.0*b.son/b.mom;
    }
    friend bool operator >= (const Fraction &a,const Fraction &b)
    {
        return 1.0*a.son/a.mom < 1.0*b.son/b.mom;
    }

    friend bool operator == (const Fraction &a,const Fraction &b)
    {
        return 1.0*a.son/a.mom == 1.0*b.son/b.mom;
    }
    friend bool operator != (const Fraction &a,const Fraction &b)
    {
        return 1.0*a.son/a.mom != 1.0*b.son/b.mom;
    }

};

int main()
{
    try
    {
        Fraction t1(-17,3),t2(-31,-12);
        cout<<"t1: "<<t1<<"    t2: "<<t2<<endl;
        cout<<"t1<t2? "<<(t1<t2)<<endl;
        cout<<"t1=t2? "<<(t1==t2)<<endl;

        cout<<"t1+t2: "<<t1+t2<<endl;
        cout<<"t1-t2: "<<t1-t2<<endl;
        cout<<"t1*t2: "<<t1*t2<<endl;
        cout<<"t1/t2: "<<t1/t2<<endl;
    }
    catch(exception)
    {
        cout<<"Error in the calculation process"<<endl;
        exit(0);
    }
    return 0;
}
