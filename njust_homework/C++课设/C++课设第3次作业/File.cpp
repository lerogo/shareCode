#include<iostream>
#include<windows.h>
#include"DateTime.h"
using namespace std;
class File{
    string name,type;
    double _size;
    DateTime create,modify;
public:
    File(string name="",string type="",double _size=0.0):create(),modify(){
        this->name=name;
        this->type=type;
        this->_size=_size;
    }

    void SetName(string name){
        this->name=name;
        modify.UpdataTime();
    }
    void SetType(string type){
        this->type=type;
        modify.UpdataTime();
    }
    void SetSize(double _size){
        this->_size=_size;
        modify.UpdataTime();
    }

    string GetName(){
        return name;
    }
    string GetType(){
        return type;
    }
    double GetSize(){
        return _size;
    }
    DateTime GetCreateTime(){
        return create;
    }
    DateTime GetModifyTime(){
        return modify;
    }

    void show(){
        cout<<"�ļ���: "<<name<<"."<<type<<endl;
        cout<<"��С:"<<_size<<" KB"<<endl;
        cout<<"����";
        create.show();
        cout<<"�޸�";
        modify.show();
    }
};

int main(){
    cout<<"Now this is the file"<<endl;
    File file("test1","zip",1.2);
    file.show();

    cout<<endl<<"Now Sleep 3s"<<endl<<endl;
    Sleep(3000);

    cout<<"Now modify the file"<<endl;
    file.SetName("test2");
    file.SetType("mp4");
    file.SetSize(1325);
    file.show();

    cout<<endl<<"Now get the file's info"<<endl;
    cout<<"�ļ�����: "<<file.GetName()<<endl;
    cout<<"�ļ�������: "<<file.GetType()<<endl;
    cout<<"�ļ���С��: "<<file.GetSize()<<" KB"<<endl;
    cout<<"����";
    file.GetCreateTime().show();
    cout<<"�޸�";
    file.GetModifyTime().show();
    return 0;
}





