vector<LL>graph[MAX];
//index[i]��ʾi�ǵڼ��������ʵĽ��,lowLink[i]��ʾ��i����������߿ɵ�������нڵ�����С��index,sccno[i]��ʾi������ǿ��ͨ�����ı��
LL index[MAX],lowLink[MAX],sccno[MAX],dfsNo=0,scc_cnt=0;
stack<LL>s;//�㷨����ʱsΪ��
void DFS(LL v){
    index[v]=lowLink[v]=++dfsNo;
    s.push(v);
    for(LL i:graph[v]){
        if(index[i]==0){
            DFS(i);
            lowLink[v]=min(lowLink[v],lowLink[i]);
        }else if(sccno[i]==0)
            lowLink[v]=min(lowLink[v],index[i]);
    }
    if(lowLink[v]==index[v]){//��һ��ǿ��ͨ��֧�ĸ����
        ++scc_cnt;
        LL t;
        do{
            t=s.top();
            s.pop();
            sccno[t]=scc_cnt;
        }while(t!=v);
    }
}
void Tarjan(){
    for(LL i=1;i<=n;++i)//��������1~n���
        if(index[i]==0)
            DFS(i);
}
