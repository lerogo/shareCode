stack<LL>s;
s.push(start);//起始顶点入栈
while(!s.empty()){
    LL v=s.top(),i;
    for(i=0;i<graph[v].size();++i){//遍历该点能到达的结点
        LL w=graph[v][i];
        if(!visit[v][w]){//该边没有被访问过
            s.push(w);//顶点w入栈
            visit[v][w]=visit[w][v]=true;//该边已被访问
            break;//跳出循环
        }
    }
    if(i==graph[v].size()){//没有还未访问的边
        path.push_back(v);//顶点v加入欧拉序列
        s.pop();//出栈
    }
}
