//把R进制字符串s转换成十进制数
LL strToDemical(const string&s,LL R=10){
    LL n=0;
    for(char c:s)
        n=n*R+(c-'0');
    return n;
}
//把十进制数m转换成R进制数组z
LL demicalToR(LL m,LL z[],LL R=10){
    LL num=0;
    do{
        z[num++]=m%R;
        m/=R;
    }while(m!=0);
    reverse(z,z+num);
    return num;
}
