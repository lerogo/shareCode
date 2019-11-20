LL father[MAX];
void init(LL n){//初始化并查集
    iota(father,father+n,0);
}
LL findFather(LL x){//寻找根结点并进行路径压缩
    if(x==father[x])
        return x;
    LL temp=findFather(father[x]);
    father[x]=temp;
    return temp;
}
void unionSet(LL a,LL b){//合并两个集合
    LL ua=findFather(a),ub=findFather(b);
    if(ua!=ub)
        father[ua]=ub;
}
LL countRoot(LL n){//求出并查集中有几个集合
    LL num=0;
    for(LL i=0;i<n;++i)
        if(father[i]==i)
            ++num;
    return num;
}
