//ͼ���ڽӾ���洢����Ϊ��Ȩͼ��graph[i][i]=0,��Ȩ�ļ�ΪȨֵ�������ΪINF=0x3fffffff
//��Ϊ��Ȩͼ����i��j֮���бߣ�graph[i][j]=1�������Ϊ0
void floyd(){
    for(LL i=0;i<MAX;++i)
        for(LL j=0;j<MAX;++j)
            dis[i][j]=graph[i][j];
    for(LL k=0;k<MAX;++k)
        for(LL i=0;i<MAX;++i)
            for(LL j=0;j<MAX;++j)
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);//��Ȩͼ���������
                dis[i][j]=dis[i][j]||(dis[i][k]&&dis[k][j]);//��Ȩͼ���������
}
