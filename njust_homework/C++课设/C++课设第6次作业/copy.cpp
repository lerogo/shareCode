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
        cout << "���ܴ������ļ���" << argv[1]<< endl;
        return 0;
    }
    if (!outfile)
    {
        cout << "���ܴ�Ŀ���ļ���" << argv[2]<< endl;
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
