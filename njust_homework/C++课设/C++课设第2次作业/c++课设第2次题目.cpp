#include<bits/stdc++.h>
#include<iomanip>
using namespace std;

class Data{
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

class DataTime{
	Data data;
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
	DataTime(int year,int month,int day,int hour,int min,int sec){
		data.SetYear(year);
		data.SetMonth(month);
		data.SetDay(day);
		this->hour=hour;
		this->min=min;
		this->sec=sec;
	}
	DataTime(){
		time_t now = time(0);
		tm *lct = localtime(&now);
		data.SetYear(1900 + lct->tm_year);
		data.SetMonth(1 + lct->tm_mon);
		data.SetDay(lct->tm_mday);
		hour = lct->tm_hour;
		min = lct->tm_min;
		sec = lct->tm_sec;
	}
};
void DataTime::show(){
	cout<<"时间是："<<endl;
	//格式化输出 
	cout<<setfill('0')<<setw(4)<<data.GetYear()<<"年"<<  setfill('0')<<setw(2)<<data.GetMonth()<<"月"<<  setfill('0')<<setw(2)<<data.GetDay()<<"日 ";
	cout<<setfill('0')<<setw(2)<<hour<<":"<<setfill('0')<<setw(2)<<min<<":"<<setfill('0')<<setw(2)<<sec<<endl<<endl;
}

void DataTime::SetYear(int year){
		data.SetYear(year);
}

void DataTime::SetMonth(int month){
		data.SetMonth(month);
}

void DataTime::SetDay(int day){
		data.SetDay(day);
}

void DataTime::SetHour(int hour){
		this->hour = hour;
}

void DataTime::SetMin(int min){
		this->min = min;
}

void DataTime::SetSec(int sec){
		this->sec = sec;
}


int DataTime::GetYear(){
	return data.GetYear();	
}

int DataTime::GetMonth(){
	return data.GetMonth();	
}
int DataTime::GetDay(){
	return data.GetDay();	
}
int DataTime::GetHour(){
	return hour;	
}
int DataTime::GetMin(){
	return min;	
}
int DataTime::GetSec(){
	return sec;	
}


int main(){
	DataTime datatime;
	
	cout<<"This is now"<<endl;
	datatime.show();
	
	cout<<"Now get data"<<endl;
	cout<<"year: "<<setfill('0')<<setw(4)<<datatime.GetYear()<<endl;
	cout<<"month: "<<setfill('0')<<setw(2)<<datatime.GetMonth()<<endl;
	cout<<"day: "<<setfill('0')<<setw(2)<<datatime.GetDay()<<endl;
	cout<<"hour: "<<setfill('0')<<setw(2)<<datatime.GetHour()<<endl;
	cout<<"min: "<<setfill('0')<<setw(2)<<datatime.GetMin()<<endl;
	cout<<"sec: "<<setfill('0')<<setw(2)<<datatime.GetSec()<<endl;
	
	cout<<endl<<endl<<"Now set data"<<endl;
	datatime.SetYear(2050);
	datatime.SetMonth(1);
	datatime.SetDay(1);
	datatime.SetHour(6);
	datatime.SetMin(1);
	datatime.SetSec(12);
	datatime.show();
	
	cout<<"Now get data"<<endl;
	cout<<"year: "<<setfill('0')<<setw(4)<<datatime.GetYear()<<endl;
	cout<<"month: "<<setfill('0')<<setw(2)<<datatime.GetMonth()<<endl;
	cout<<"day: "<<setfill('0')<<setw(2)<<datatime.GetDay()<<endl;
	cout<<"hour: "<<setfill('0')<<setw(2)<<datatime.GetHour()<<endl;
	cout<<"min: "<<setfill('0')<<setw(2)<<datatime.GetMin()<<endl;
	cout<<"sec: "<<setfill('0')<<setw(2)<<datatime.GetSec()<<endl;
	
	return 0;
}

