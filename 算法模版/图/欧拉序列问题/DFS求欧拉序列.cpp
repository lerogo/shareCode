void DFS(LL v){
    for(LL i:graph[v]){
        if(!edges[i].visit){
            edges[i].visit=edges[i^1].visit=true;//有向图、无向图在这是不同的
            DFS(edges[i].to);
        }
    }
    ans.push_back(v);
}
//注意ans数组必须倒序输出才是正确的欧拉序列。假设有m条边，则判断图是否连通的语句是ans.size()==m+1
