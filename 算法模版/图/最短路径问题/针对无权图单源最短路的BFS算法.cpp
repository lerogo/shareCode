//��Ȩͼ��Դ���·��BFS�㷨�ı߳���β����⣬�߲�����������Ϣ������Ҫʹ������Ĵ洢�ṹ��graph[i]�д洢��ֱ����i�Ž���ܵ���Ľ����
vector<LL>graph[MAX];//graph[i][j]��ʾ���i�ܵ���ĵ�j�������
void BFS(LL s){
    queue<LL>q;
    memset(inQueue,0,sizeof(inQueue));
    dis[s]=0;
    q.push(s);
    inQueue[s]=true;
    while(!q.empty()){
        LL p=q.front();
        q.pop();
        for(LL i:graph[p]){
            if(!inQueue[i]){
                q.push(i);
                dis[i]=dis[p]+1;
                inQueue[i]=true;
            }
        }
    }
}
