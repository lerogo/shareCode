void insertEdge(LL from,LL to,LL cap){//�����
    graph[from].push_back(edges.size());
    edges.push_back(Edge(from,to,cap,0));
    graph[to].push_back(edges.size());
    edges.push_back(Edge(to,from,0,0));
}
LL a[MAX],p[MAX];//a�����ʾԴ�㵽���a[i]�Ĳ���,p�����ʾ���·���ϵ�����p[i]�ı���edges�����е����
LL MaxFlow(LL s,LL t){//������㷨,sΪԴ��,tΪ���
    LL flow=0;//�������
    while(true){
        memset(a,0,sizeof(a));//��Դ�㵽��ÿ�����Ĳ�����ʼ��Ϊ0
        //������ȱ������Ҵ�Դ�㵽���������·
        queue<LL>q;
        q.push(s);
        a[s]=LONG_LONG_MAX;//���Ĳ�����Ϊ�����
        while(!q.empty()){
            LL x=q.front();
            q.pop();
            for(LL i:graph[x]){//������xΪ���ı�
                Edge&e=edges[i];
                if(a[e.to]==0&&e.cap>e.flow){//��ǰ�ߵ��յ�Ĳ���Ϊ0��������������
                    p[e.to]=i;//���µ�����յ�ıߵı��
                    a[e.to]=min(a[x],e.cap-e.flow);//����Դ�㵽���յ�Ĳ���
                    q.push(e.to);//ѹ�����
                }
            }
            if(a[t]!=0)//�յ�Ĳ�����Ϊ�㣬����ѭ��
                break;
        }
        if(a[t]==0)//�յ�Ĳ���Ϊ�㣬��ʾ����������·�ˣ����������ѭ��
            break;
        for(LL u=t;u!=s;u=edges[p[u]].from){//�ӻ����ǰ��������·��������ÿ������·������
            edges[p[u]].flow+=a[t];
            edges[p[u]^1].flow-=a[t];
        }
        flow+=a[t];//�����������
    }
    return flow;
}
