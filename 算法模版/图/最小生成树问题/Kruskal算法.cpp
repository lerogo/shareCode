priority_queue<Edge>edges;//�ߵ����ȼ�����
LL father[MAX];
LL findFather(LL x){//���Ҹ��׽�㲢����·��ѹ��
    if(x==father[x])
        return x;
    LL temp=findFather(father[x]);
    father[x]=temp;
    return temp;
}
LL Kruskal(){//�����С��������Ȩֵ֮��
    iota(father,father+MAX,0);//��ʼ�����鼯
    LL sumCost=0; //sumCost��ʾ������С�������ĸ���Ȩֵ֮��
    while(!edges.empty()){
        Edge e=edges.top();
        edges.pop();//������ǰ�����б�Ȩ��С�ı�
        LL ua=findFather(e.from),ub=findFather(e.to);
        if(ua!=ub){
            sumCost+=e.cost;
            father[ua]=ub;
        }
    }
    return sumCost;//������������Ȩֵ֮��
}
