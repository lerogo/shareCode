void calDay(int sYear, int sMonth, int sDay, 
                    int eYear, int eMonth, int eDay){
    int sum = 0;
    sum -= sDay;
    sum += eDay;

    monthArr[2] = 28;
    if (isLeapYear(sYear))  monthArr[2] = 29;
    for (int i=1;i<sMonth;++i) sum -= monthArr[i];

    monthArr[2] = 28;
    if (isLeapYear(eYear))  monthArr[2] = 29;
    for (int i=1;i<eMonth;++i) sum += monthArr[i];

    while (sYear<eYear) {
        sum += 365;
        if(isLeapYear(sYear)) ++sum;
        ++sYear;
    }
    cout<<sum<<endl;
}