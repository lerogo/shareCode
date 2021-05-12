#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
using namespace std;

class TMatrix
{
public:
    int row,col;
    double **matrix;
    TMatrix(int row,int col)
    {
        this->row=row;
        this->col=col;
        matrix=new double *[row];
        for(int i=0; i<row; ++i)
            matrix[i]=new double [col];
    }
    ~TMatrix()
    {
        for(int i=0; i<row; ++i)
            delete [] matrix[i];
        delete [] matrix;
    }
    void show(){
        for(int i=0; i<row; ++i){
            for(int j=0; j<col; ++j)
                cout<<matrix[i][j]<<" ";
            cout<<endl;
        }
    }
    bool read(string filename,string type="binary")
    {
        if(type=="txt")
        {
            ifstream infile(filename.c_str());
            if(!infile)
            {
                cerr<<"cannot open file "<< filename <<endl;
                exit(0);
            }
            for(int i=0; i<row; ++i)
                for(int j=0; j<col; ++j)
                    infile>>matrix[i][j];
            infile.close();
            return true;
        }
        if(type=="binary")
        {
            ifstream infile(filename.c_str(),ios::binary);
            if(!infile)
            {
                cerr<<"cannot open file "<< filename <<endl;
                exit(0);
            }
            infile.read((char *)matrix,sizeof(double)*row*col);
            infile.close();
            return true;
        }
        return false;
    }
    bool write(string filename,string type="binary")
    {
        if(type=="txt")
        {
            ofstream outfile(filename.c_str(),ios::out);
            if(!outfile)
            {
                cerr<<"cannot open file "<< filename <<endl;
                exit(0);
            }
            for(int i=0; i<row; ++i)
            {
                for(int j=0; j<col; ++j)
                {
                    outfile<<matrix[i][j]<<" ";
                }
                outfile<<endl;
            }
            outfile.close();
            return true;
        }
        if(type=="binary")
        {
            ofstream outfile(filename.c_str(),ios::binary);
            if(!outfile)
            {
                cerr<<"cannot open file "<< filename <<endl;
                exit(0);
            }
            outfile.write((char *)matrix,sizeof(double)*row*col);
            outfile.close();
            return true;
        }
        return false;
    }
};

int main()
{
    TMatrix t1(3,4);
    TMatrix t2(3,4);

    t1.read ("test.txt","txt");
    t1.write("test1.txt","txt");
    t1.write("test2.dat","binary");
    t2.read("test2.dat","binary");

    t1.show();
    t2.show();
    return 0;
}
