#include <iostream>
#include<iomanip>

using namespace std;

int week(int year, int month);

int main() {
    int year = 2020;
    int month = 2;
    int w = week(year, month);

    return 0;
}


int week(int year, int month)   //求出日期对应的星期函数
{
    int arr[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
        arr[2] = 29;
    }
    int s = 0;
    for (int i = 1; i < month; ++i) {
        s += arr[i];
    }
    s = (year - 1 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400 + 1 + s) % 7;     //所求日期的星期数
    cout << setw(6) << "日" << setw(6) << "一" << setw(6) << "二" << setw(6) << "三" << setw(6) << "四" << setw(6) << "五" << setw(6) << "六" << endl;

    for (int j = 0; j < s; j++)
    {
        cout << setw(6) << "";
    }


    for (int t = 1; t <= arr[month]; t++)
    {
        cout << setw(6) << t;
        s = (s + 1) % 7;
        if (s % 7 == 0)
        {
            cout << endl;
        }
    }

    return s;
}
