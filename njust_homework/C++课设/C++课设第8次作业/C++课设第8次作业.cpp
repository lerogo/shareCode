#include<iostream>
using namespace std;

template <class T> class TMatrix{
	T **matrix;
	int row,col;
public:
    //构造函数
	TMatrix(){row=0; col=0;matrix=nullptr;}
	TMatrix(int row,int col){
		this->row=row;
		this->col=col;
		matrix = new T * [row];
		for(int i=0;i<row;++i)
			matrix[i] = new T [col];
		for(int i=0;i<row;++i){
			for(int j=0;j<col;++j){
				matrix[i][j]=0;
			}
		}
	}
	//拷贝构造
	TMatrix(const TMatrix &a){
		row = a.row;
		col = a.col;

		matrix = new T * [row];
		for(int i=0;i<row;++i)
			matrix[i] = new T [col];

		for(int i=0;i<row;++i)
			for(int j=0;j<col;++j)
				matrix[i][j] = a.matrix[i][j];
	}
    //移动构造
	TMatrix (TMatrix && a)
		:row(a.row),col(a.col){
		this->matrix=a.matrix;
		a.row=0;a.col=0;
		a.matrix=nullptr;
	}
    //析构
	virtual ~ TMatrix(){
	    if(matrix != nullptr){
            for(int i=0; i<row; ++i)
                delete [] matrix[i];
            delete [] matrix;
        }
	}

	void show(){
		for(int i=0;i<row;++i){
			for(int j=0;j<col;++j){
				cout<<matrix[i][j]<<" ";
			}
			cout<<endl;
		}
	}

	void setMatrix (int i,int j,int value){
		matrix[i][j] = value;
	}
	int getRow() { return row; }
	int getCol() { return col; }

	TMatrix operator + (const TMatrix &a){
		if(row != a.row || col != a.col){
			cout<<"cannot cal the matrix"<<endl;
			return *this;
		}
		TMatrix *t=new TMatrix (row,col);
		for(int i=0;i<row;++i)
			for(int j=0;j<col;++j)
				t->matrix[i][j] = matrix[i][j] + a.matrix[i][j];
		return *t;
	}

	TMatrix operator - (const TMatrix &a){
		if(row != a.row || col != a.col){
			cout<<"cannot cal the matrix"<<endl;
			return *this;
		}
		TMatrix *t=new TMatrix (row,col);
		for(int i=0;i<row;++i)
			for(int j=0;j<col;++j)
				t->matrix[i][j] = matrix[i][j] - a.matrix[i][j];
		return *t;
	}

	TMatrix operator * (const TMatrix &a){
		if(col != a.row){
			cout<<"cannot cal the matrix"<<endl;
			return *this;
		}
		TMatrix *t=new TMatrix (row,row);
		for (int i=0; i<row ;++i){
			for(int j=0;j<row;++j){
				for(int k=0;k<col;++k){
					t->matrix[i][j] += matrix[i][k] * a.matrix[k][j];
				}
			}
		}
		return *t;
	}

	TMatrix &operator = (const TMatrix &a){
        if(matrix != nullptr){
            for(int i=0; i<row; ++i)
                delete [] matrix[i];
            delete [] matrix;
        }
		row = a.row;
		col = a.col;

		matrix = new T * [row];
		for(int i=0;i<row;++i)
			matrix[i] = new T [col];

		for(int i=0;i<row;++i)
			for(int j=0;j<col;++j)
				matrix[i][j] = a.matrix[i][j];
	}

	friend bool operator == (const TMatrix &a , const TMatrix &b) {
		if(&a==&b) return true;
		if(a.row!=b.row||a.col!=b.col) return false;
		for(int i=0;i<a.row;++i)
			for(int j=0;j<a.col;++j)
				if(a.matrix[i][j] != b.matrix[i][j]) return false;
		return true;
	}
};

int main(){

	TMatrix <int> t1(3,2),t2(2,3);
	int cnt=0;
	for(int i=0;i<3;++i){
		for(int j=0;j<2;++j){
			t1.setMatrix(i,j,++cnt);
		}
	}
	for(int i=0;i<2;++i){
		for(int j=0;j<3;++j){
			t2.setMatrix(i,j,++cnt);
		}
	}
	cout<<"t1:"<<endl;
	t1.show();
	cout<<endl<<"t2:"<<endl;
	t2.show();
	cout<<endl<<"t3(t1*t2):"<<endl;
	TMatrix <int> t3;
	t3=t1*t2;
	t3.show();

	cout<<endl<<"t1+t1 :"<<endl;
    (t1+t1).show();
    cout<<endl<<"t1-t1 :"<<endl;
    (t1-t1).show();

	return 0;
}

















