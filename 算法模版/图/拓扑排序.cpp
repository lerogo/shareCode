//�����������β����⣬�߲�����������Ϣ������Ҫʹ������Ĵ洢�ṹ��graph[i]�д洢��ֱ����i�Ž���ܵ���Ľ����
bool topSort(vector<LL>&top){//degree�洢���ڵ�����
    queue<LL>q;//�������Ϊ��Ľ��
    for(LL i=0;i<=MAX;++i)//�����Ϊ��Ľ����������
        if(degree[i]==0)
            q.push(i);
    while(!q.empty()){//���в���
        LL p=q.front();//�������׽��
        q.pop();
        top.push_back(p);
        for(LL i:graph[p])//�����ý���ܵ���Ľ��
            if(--degree[i]==0)//�����ܵ��������ȣ�������Ϊ��
                q.push(i);//ѹ�����
    }
    return top.size()==MAX;
}
