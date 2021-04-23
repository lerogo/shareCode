#include<iostream>
using namespace std;
int main()
{
	int a,b,c,d=36;
	for(a=1;a<=d/4;a++)
		for(b=1;b<d/2;b++)
			for(c=2;c<2*d;c+=2)
				if((a+b+c)==d&&(4*a+2*b+c/2)==d)
				cout<<"男人:"<<a<<'\t'<<"女人："<<b<<'\t'<<"孩子："<<c<<endl; 
	return 0; 
}
