#include<iostream>
#include<fstream>
using namespace std;
int main(int argc, char* argv[])
{
    if(argc<3)
    {
        cout<<"Format exefile datafile"<<endl;
        return 0;
    }
    ifstream infile(argv[1],ios::in);
    ofstream outfile(argv[2]);
    if (!infile)
    {
        cout << "不能打开输入文件：" << argv[1]<< endl;
        return 0;
    }
    if (!outfile)
    {
        cout << "不能打开目的文件：" << argv[2]<< endl;
        return 0;
    }
    infile >> noskipws;
    char ch;
    while (infile>>ch)
        outfile << ch;
    infile.close();
    outfile.close();
    return 0;
}
