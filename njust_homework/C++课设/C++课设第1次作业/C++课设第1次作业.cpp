#include<iostream>
#include<stdlib.h>
using namespace std;
class Cat {
    unsigned int age;
    double weight;
    string name,color;
public:
    void setBasic(string name,unsigned int age,double weight) {
        this->name=name;
        this->age=age;
        this->weight=weight;
    }
    void setColor(string color) {
        this->color=color;
    }

    void print() {
        cout<<"the cute cat is: "<<name;
        cout<<"\tits age is "<<age<<" years old; its weight is "<<weight<<"kg; it is "<<color<<endl;
    }
    unsigned int getAge() {
        return age;
    }
    double getWeight() {
        return weight;
    }
    string getName() {
        return name;
    }
    string getColor() {
        return color;
    }
};

int main() {
    Cat cat1,cat2;
    cout<<"it is cat1:"<<endl;
    cat1.setBasic("TOM",3,3.6);
    cat1.setColor("Blue and white");
    cat1.print();
    cout<<"cat1's name: "<<cat1.getName()<<endl;
    cout<<"cat1's age: "<<cat1.getAge()<<endl;
    cout<<"cat1's weight: "<<cat1.getWeight()<<"kg"<<endl;
    cout<<"cat1's color: "<<cat1.getColor()<<endl;

    cout<<endl<<"now is cat2:"<<endl;
    cat2=cat1;
    cat2.print();
    cout<<"cat2's name: "<<cat2.getName()<<endl;
    cout<<"cat2's age: "<<cat2.getAge()<<endl;
    cout<<"cat2's weight: "<<cat2.getWeight()<<"kg"<<endl;
    cout<<"cat2's color: "<<cat2.getColor()<<endl;

    cout<<endl<<"now updata cat2:"<<endl;
    cat2.setBasic("TIM",2,3.2);
    cat2.setColor("black");
    cat2.print();
    cout<<"cat2's name: "<<cat2.getName()<<endl;
    cout<<"cat2's age: "<<cat2.getAge()<<endl;
    cout<<"cat2's weight: "<<cat2.getWeight()<<"kg"<<endl;
    cout<<"cat2's color: "<<cat2.getColor()<<endl;

    system("pause");
    return 0;
}
