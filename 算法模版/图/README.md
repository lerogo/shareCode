当涉及到的边除了首尾结点外还需要有其他信息，例如是否已被访问、该边的权值等时，采取如下方法存储图：
```cpp
struct Edge{//存储边的结构体
    LL from,to;//首尾结点
    LL cap,flow;//该边的容量、残量（最大流算法使用）
    bool visit;//欧拉序列使用
    LL cost;//最短路问题使用
    ······
    Edge(LL f,LL t,······):from(f),to(t),cap(c),flow(fl) {}
};
vector<Edge>edges;//存储所有边
vector<LL>graph[MAX];//graph[i][j]表示i号结点的第j条边在edges数组中的序号
```
注意，如果是无向图，则把一条边及其反向边相邻存储，则当已知一条边在edges数组中的序号为`i`时，其反向边在edges数组中的序号为`i^1`
