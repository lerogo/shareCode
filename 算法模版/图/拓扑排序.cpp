//拓扑排序除首尾结点外，边不包含其他信息，不需要使用上面的存储结构，graph[i]中存储的直接是i号结点能到达的结点编号
bool topSort(vector<LL>&top){//degree存储各节点的入度
    queue<LL>q;//储存入度为零的结点
    for(LL i=0;i<=MAX;++i)//将入度为零的结点放入队列中
        if(degree[i]==0)
            q.push(i);
    while(!q.empty()){//队列不空
        LL p=q.front();//弹出队首结点
        q.pop();
        top.push_back(p);
        for(LL i:graph[p])//遍历该结点能到达的结点
            if(--degree[i]==0)//减少能到达结点的入度，如果入度为零
                q.push(i);//压入队列
    }
    return top.size()==MAX;
}
