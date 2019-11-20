LL father[MAX];
void init(LL n){//��ʼ�����鼯
    iota(father,father+n,0);
}
LL findFather(LL x){//Ѱ�Ҹ���㲢����·��ѹ��
    if(x==father[x])
        return x;
    LL temp=findFather(father[x]);
    father[x]=temp;
    return temp;
}
void unionSet(LL a,LL b){//�ϲ���������
    LL ua=findFather(a),ub=findFather(b);
    if(ua!=ub)
        father[ua]=ub;
}
LL countRoot(LL n){//������鼯���м�������
    LL num=0;
    for(LL i=0;i<n;++i)
        if(father[i]==i)
            ++num;
    return num;
}
