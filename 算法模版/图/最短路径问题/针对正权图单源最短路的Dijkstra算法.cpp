typedef pair<LL,LL> pii;
void Dijkstra(LL s){
    priority_queue<pii,vector<pii>,greater<pii>>pq;//pii的first成员存储dis，second成员存储结点编号
    fill(dis,dis+MAX,LONG_LONG_MAX);
    dis[s]=0;
    pq.push({0,s});
    while(!pq.empty()){
        pii p=pq.top();
        pq.pop();
        if(dis[p.second]!=p.first)
            continue;
        for(LL i:graph[p.second]){
            Edge&e=edges[i];
            if(dis[e.to]>dis[p.second]+e.cost){
                dis[e.to]=dis[p.second]+e.cost;
                pq.push({dis[e.to],e.to});
            }
        }
    }
}
