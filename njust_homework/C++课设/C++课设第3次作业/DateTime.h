#include<iostream>
#include<time.h>
#include<iomanip>
using namespace std;

class Date{
	int year,month,day;
public:
	void SetYear(int year){
		this->year = year;
	}

	void SetMonth(int month){
		this->month = month;
	}

	void SetDay(int day){
		this->day = day;
	}

	int GetYear(){
	return year;
	}

	int GetMonth(){
		return month;
	}
	int GetDay(){
		return day;
	}
};

class DateTime{
	Date date;
	int hour,min,sec;

public:
	void show();//show()函数

	void SetYear(int);//set year
	void SetMonth(int);//set month
	void SetDay(int);//set day
	void SetHour(int);//set hour
	void SetMin(int);//set min
	void SetSec(int);//set sec

	int GetYear();//Get year
	int GetMonth();//Get month
	int GetDay();//Get day
	int GetHour();//Get hour
	int GetMin();//Get min
	int GetSec();//Get sec

	//构造函数
	DateTime(int year,int month,int day,int hour,int min,int sec){
		date.SetYear(year);
		date.SetMonth(month);
		date.SetDay(day);
		this->hour=hour;
		this->min=min;
		this->sec=sec;
	}
	DateTime(){
		time_t now = time(0);
		tm *lct = localtime(&now);
		date.SetYear(1900 + lct->tm_year);
		date.SetMonth(1 + lct->tm_mon);
		date.SetDay(lct->tm_mday);
		hour = lct->tm_hour;
		min = lct->tm_min;
		sec = lct->tm_sec;
	}
    void UpdataTime(){
        time_t now = time(0);
		tm *lct = localtime(&now);
		date.SetYear(1900 + lct->tm_year);
		date.SetMonth(1 + lct->tm_mon);
		date.SetDay(lct->tm_mday);
		hour = lct->tm_hour;
		min = lct->tm_min;
		sec = lct->tm_sec;
    }
};
void DateTime::show(){
	cout<<"时间是：";
	//格式化输出
	cout<<setfill('0')<<setw(4)<<date.GetYear()<<"年"<<  setfill('0')<<setw(2)<<date.GetMonth()<<"月"<<  setfill('0')<<setw(2)<<date.GetDay()<<"日 ";
	cout<<setfill('0')<<setw(2)<<hour<<":"<<setfill('0')<<setw(2)<<min<<":"<<setfill('0')<<setw(2)<<sec<<endl;
}

void DateTime::SetYear(int year){
		date.SetYear(year);
}

void DateTime::SetMonth(int month){
		date.SetMonth(month);
}

void DateTime::SetDay(int day){
		date.SetDay(day);
}

void DateTime::SetHour(int hour){
		this->hour = hour;
}

void DateTime::SetMin(int min){
		this->min = min;
}

void DateTime::SetSec(int sec){
		this->sec = sec;
}


int DateTime::GetYear(){
	return date.GetYear();
}

int DateTime::GetMonth(){
	return date.GetMonth();
}
int DateTime::GetDay(){
	return date.GetDay();
}
int DateTime::GetHour(){
	return hour;
}
int DateTime::GetMin(){
	return min;
}
int DateTime::GetSec(){
	return sec;
}

/*
int main(){
	DateTime dt;

	cout<<"This is now"<<endl;
	dt.show();

	cout<<"Now get date"<<endl;
	cout<<"year: "<<setfill('0')<<setw(4)<<dt.GetYear()<<endl;
	cout<<"month: "<<setfill('0')<<setw(2)<<dt.GetMonth()<<endl;
	cout<<"day: "<<setfill('0')<<setw(2)<<dt.GetDay()<<endl;
	cout<<"hour: "<<setfill('0')<<setw(2)<<dt.GetHour()<<endl;
	cout<<"min: "<<setfill('0')<<setw(2)<<dt.GetMin()<<endl;
	cout<<"sec: "<<setfill('0')<<setw(2)<<dt.GetSec()<<endl;

	cout<<endl<<endl<<"Now set date"<<endl;
	dt.SetYear(2050);
	dt.SetMonth(1);
	dt.SetDay(1);
	dt.SetHour(6);
	dt.SetMin(1);
	dt.SetSec(12);
	dt.show();

	cout<<"Now get date"<<endl;
	cout<<"year: "<<setfill('0')<<setw(4)<<dt.GetYear()<<endl;
	cout<<"month: "<<setfill('0')<<setw(2)<<dt.GetMonth()<<endl;
	cout<<"day: "<<setfill('0')<<setw(2)<<dt.GetDay()<<endl;
	cout<<"hour: "<<setfill('0')<<setw(2)<<dt.GetHour()<<endl;
	cout<<"min: "<<setfill('0')<<setw(2)<<dt.GetMin()<<endl;
	cout<<"sec: "<<setfill('0')<<setw(2)<<dt.GetSec()<<endl;

	return 0;
}

*/
