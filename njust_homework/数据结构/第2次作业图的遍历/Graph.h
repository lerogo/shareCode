#ifndef OJ_GRAPH_H
#define OJ_GRAPH_H

#include <iostream>
#include <string>
#include <queue>

using namespace std;
const unsigned MAX_VEC_NUM = 100;

// 使用邻接矩阵 的 无向图 进行广度遍历
class Graph {
private:
    struct {
        string vexs[MAX_VEC_NUM];           //顶点信息
        struct {
            bool adj;        //是否相邻
            string info;     //弧相关信息
        } arcs[MAX_VEC_NUM][MAX_VEC_NUM];;    //arcs[i][j] i点与j点
        unsigned vexnum;    //顶点个数
        unsigned arcnum;    //边个数
    } graph;
    bool visited[MAX_VEC_NUM];  //是否遍历过了

public:
    //初始化 访问过为假，点名字为""等
    Graph() {
        for (unsigned i = 0; i < MAX_VEC_NUM; ++i) {
            graph.vexs[i] = "";
            visited[i] = false;
            for (unsigned j = 0; j < MAX_VEC_NUM; ++j) {
                graph.arcs[i][j].adj = false;
                graph.arcs[i][j].info = "";
            }
        }
    }

    void createGraph();     //创建图
    unsigned locateVex(string u);   //返回u的位置
    void BFS(unsigned index);       //广度遍历  非递归调用
};

unsigned Graph::locateVex(string u) {
    for (unsigned i = 0; i < graph.vexnum; ++i) {
        if (u == graph.vexs[i]) return i;
    }
    return -1;
}   //unsigned Graph::locateVex(string u)

void Graph::createGraph() {
    cout << "输入无向图的顶点个数，边的个数" << endl;
    cin >> graph.vexnum >> graph.arcnum;
    if (graph.vexnum > MAX_VEC_NUM) {
        cerr << "点太多了！" << endl;
        exit(-1);
    }
    //输入每个点
    for (unsigned i = 0; i < graph.vexnum; ++i) {
        cout << "请输入点 " << i + 1 << "：" << endl;
        cin >> graph.vexs[i];
    }
    //输入边信息
    string str1, str2;
    for (unsigned i = 0; i < graph.arcnum; ++i) {
        cout << "请输入第 " << i + 1 << " 条边：" << endl;
        cin >> str1 >> str2;
        unsigned a = this->locateVex(str1);
        unsigned b = this->locateVex(str2);
        if(a==unsigned(-1)||b==unsigned(-1)){
            cout<<"查无此点"<<endl;
            --i;
            continue;
        }
        graph.arcs[a][b].adj = 1;
        graph.arcs[b][a].adj = 1;
    }
}//void Graph::createGraph()

void Graph::BFS(unsigned index) {
    //如果index没有
    if (index >= graph.vexnum) return;
    //设置遍历的点书目
    unsigned visitNum = 0;
    //储存点输出顺序
    queue<unsigned> Q;
    //第一个点开始
    Q.push(index);
    visited[index] = true;
    while (visitNum < graph.vexnum) {
        //如果为空且还有点没有遍历 则选一个序号最小且未被访问的点
        if (Q.empty()) {
            for (unsigned i = 0; i < graph.vexnum; ++i) {
                if (!visited[i]) {
                    Q.push(i);
                    visited[i] = true;
                    break;
                }
            }
        }
        // 拿到队列中的第一个元素
        index = Q.front();
        Q.pop();
        cout << graph.vexs[index] << " ";
        ++visitNum;
        //选择与此点相邻的点 遍历
        for (unsigned i = 0; i < graph.vexnum; ++i) {
            if (graph.arcs[index][i].adj && !visited[i]) {
                Q.push(i);
                visited[i] = true;
            }
        }
    }

    //重置
    for (unsigned i = 0; i < graph.vexnum; ++i) {
        visited[i] = false;
    }
}   //void Graph::BFS(unsigned index)

#endif //OJ_GRAPH_H

