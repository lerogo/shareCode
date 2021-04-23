#include<iostream>
using namespace std;
int main()
{
	int year;
	cout<<"input year:";
	cin>>year;
	if(year%400==0||(year%4==0&&year%100!=0)) cout<<"is a leap year"<<endl;
	else cout<<"isn't a leap year"<<endl;
	return 0; 
}
