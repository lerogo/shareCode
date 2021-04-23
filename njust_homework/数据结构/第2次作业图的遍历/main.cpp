#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
    //freopen("./in.txt", "r", stdin);

    // 使用 邻接矩阵 的 无向图 进行 广度遍历
    Graph g1;
    g1.createGraph();
    cout<<"遍历结果："<<endl;
    g1.BFS(0);  //广度遍历  非递归调用
	cout<<endl;
	system("pause");
    return 0;
}


