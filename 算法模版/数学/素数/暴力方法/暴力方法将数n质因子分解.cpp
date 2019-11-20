unordered_map<LL,LL>factor;//��������factor�У�����ʾ�����ӣ�ֵ��ʾ�������Ӹ�����ע��map�ᰴ������
void getFactor(LL n,LL arg){//argΪ1ʱ��ʾ��n�ڷ����ϣ����˷���argΪ-1��ʾ��n�ڷ�ĸ�ϣ�������
    for(LL i=2;i<=(LL)sqrt(n*1.0);++i){
        LL j=0;
        for(;n%i==0;n/=i)
            ++j;
        if(j!=0)
            factor[i]+=arg*j;
        if(n==1)
            break;
    }
    if(n>1)
        factor[n]+=arg;
}
