//��R�����ַ���sת����ʮ������
LL strToDemical(const string&s,LL R=10){
    LL n=0;
    for(char c:s)
        n=n*R+(c-'0');
    return n;
}
//��ʮ������mת����R��������z
LL demicalToR(LL m,LL z[],LL R=10){
    LL num=0;
    do{
        z[num++]=m%R;
        m/=R;
    }while(m!=0);
    reverse(z,z+num);
    return num;
}
