unordered_map<LL,LL>factor;//��������factor�У�����ʾ�����ӣ�ֵ��ʾ�������Ӹ�����ע��map�ᰴ������
void getFactor(LL n,LL arg){//argΪ1ʱ��ʾ��n�ڷ����ϣ����˷���argΪ-1��ʾ��n�ڷ�ĸ�ϣ�������
    findPrime(n+1);//��ӡn+1���ڵ�������洢��prime��
    for(LL i:prime){
        while(n%i==0){
            factor[i]+=arg;
            n/=i;
        }
        if(n==1)
            break;
    }
}
