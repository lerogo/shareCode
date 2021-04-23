#include <iostream>
#include <string>

#include "Poly.h"

using namespace std;

int main() {
    cout<<"------------------------------------------------------------"<<endl;
    string str1 = "5x^2+ 4x ^3-   12 .12x  ^8+12x^9-12x^12+12.123x^16+1x-100";
    cout<<"str1: "<<str1<<endl;
    Poly c1(str1);
    c1.clear();
    cout<<"c1: ";
    c1.print();

    cout<<endl<<endl;
    string str2 = "5x^2+ 4x ^3 +124X^34  -   12 .12x  ^8+12x^9-12x^12+12.123x^16+12x^2+18x^6-1x+100";
    cout<<"str2: "<<str2<<endl;
    Poly c2(str2);
    c2.clear();
    cout<<"c2: ";
    c2.print();

    cout<<endl<<endl;
    cout<<"c1+c2: ";
    c1+=c2;
    c1.clear();
    c1.print();

    cout<<endl<<endl;
    cout<<"c1: ";
    c1.print();

    cout<<endl<<endl;
    Poly c3;
    c3.create(str2);
    c3.clear();
    cout<<"c3: ";
    c3.print();

    cout<<endl<<endl;
    cout<<"c1-c3: ";
    c1-=c3;
    c1.clear();
    c1.print();

    cout<<endl<<"------------------------------------------------------------"<<endl;
    system("pause");
    return 0;
}
