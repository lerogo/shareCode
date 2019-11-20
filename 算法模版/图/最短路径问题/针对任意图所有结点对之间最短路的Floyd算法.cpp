//图用邻接矩阵存储，若为有权图，graph[i][i]=0,有权的即为权值，其余均为INF=0x3fffffff
//若为无权图，若i和j之间有边，graph[i][j]=1；其余均为0
void floyd(){
    for(LL i=0;i<MAX;++i)
        for(LL j=0;j<MAX;++j)
            dis[i][j]=graph[i][j];
    for(LL k=0;k<MAX;++k)
        for(LL i=0;i<MAX;++i)
            for(LL j=0;j<MAX;++j)
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);//有权图用这条语句
                dis[i][j]=dis[i][j]||(dis[i][k]&&dis[k][j]);//无权图用这条语句
}
