stack<LL>s;
s.push(start);//��ʼ������ջ
while(!s.empty()){
    LL v=s.top(),i;
    for(i=0;i<graph[v].size();++i){//�����õ��ܵ���Ľ��
        LL w=graph[v][i];
        if(!visit[v][w]){//�ñ�û�б����ʹ�
            s.push(w);//����w��ջ
            visit[v][w]=visit[w][v]=true;//�ñ��ѱ�����
            break;//����ѭ��
        }
    }
    if(i==graph[v].size()){//û�л�δ���ʵı�
        path.push_back(v);//����v����ŷ������
        s.pop();//��ջ
    }
}
