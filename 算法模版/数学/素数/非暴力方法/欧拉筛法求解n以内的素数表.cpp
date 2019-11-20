//以下代码求解[2,n)以内的素数表（注意不包含数字n）
vector<LL>prime;//素数表存储在prime中，prime是全局变量
void findPrime(LL n){
    vector<bool>f(n,true);//i为素数，则f[i]=true;i不是素数，则f[i]=false
    for(LL i=2;i<n;++i){
        if(f[i])
            prime.push_back(i);
        for(LL j=0;j<prime.size()&&i*prime[j]<n;++j){//遍历所有已筛选出的素数
            f[i*prime[j]]=false;//i*prime[j]不是素数
            if(i%prime[j]==0)//关键
                break;
        }
    }
}
