unordered_map<LL,LL>factor;//质因子在factor中，键表示质因子，值表示该质因子个数，注意map会按键排序
void getFactor(LL n,LL arg){//arg为1时表示数n在分子上，作乘法；arg为-1表示数n在分母上，作除法
    findPrime(n+1);//打印n+1以内的素数表存储到prime中
    for(LL i:prime){
        while(n%i==0){
            factor[i]+=arg;
            n/=i;
        }
        if(n==1)
            break;
    }
}
