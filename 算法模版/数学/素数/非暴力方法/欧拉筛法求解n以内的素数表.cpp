//���´������[2,n)���ڵ�������ע�ⲻ��������n��
vector<LL>prime;//������洢��prime�У�prime��ȫ�ֱ���
void findPrime(LL n){
    vector<bool>f(n,true);//iΪ��������f[i]=true;i������������f[i]=false
    for(LL i=2;i<n;++i){
        if(f[i])
            prime.push_back(i);
        for(LL j=0;j<prime.size()&&i*prime[j]<n;++j){//����������ɸѡ��������
            f[i*prime[j]]=false;//i*prime[j]��������
            if(i%prime[j]==0)//�ؼ�
                break;
        }
    }
}
