#ifndef OJ_GRAPH_H
#define OJ_GRAPH_H

#include <iostream>
#include <string>
#include <queue>

using namespace std;
const unsigned MAX_VEC_NUM = 100;

// ʹ���ڽӾ��� �� ����ͼ ���й�ȱ���
class Graph {
private:
    struct {
        string vexs[MAX_VEC_NUM];           //������Ϣ
        struct {
            bool adj;        //�Ƿ�����
            string info;     //�������Ϣ
        } arcs[MAX_VEC_NUM][MAX_VEC_NUM];;    //arcs[i][j] i����j��
        unsigned vexnum;    //�������
        unsigned arcnum;    //�߸���
    } graph;
    bool visited[MAX_VEC_NUM];  //�Ƿ��������

public:
    //��ʼ�� ���ʹ�Ϊ�٣�������Ϊ""��
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

    void createGraph();     //����ͼ
    unsigned locateVex(string u);   //����u��λ��
    void BFS(unsigned index);       //��ȱ���  �ǵݹ����
};

unsigned Graph::locateVex(string u) {
    for (unsigned i = 0; i < graph.vexnum; ++i) {
        if (u == graph.vexs[i]) return i;
    }
    return -1;
}   //unsigned Graph::locateVex(string u)

void Graph::createGraph() {
    cout << "��������ͼ�Ķ���������ߵĸ���" << endl;
    cin >> graph.vexnum >> graph.arcnum;
    if (graph.vexnum > MAX_VEC_NUM) {
        cerr << "��̫���ˣ�" << endl;
        exit(-1);
    }
    //����ÿ����
    for (unsigned i = 0; i < graph.vexnum; ++i) {
        cout << "������� " << i + 1 << "��" << endl;
        cin >> graph.vexs[i];
    }
    //�������Ϣ
    string str1, str2;
    for (unsigned i = 0; i < graph.arcnum; ++i) {
        cout << "������� " << i + 1 << " ���ߣ�" << endl;
        cin >> str1 >> str2;
        unsigned a = this->locateVex(str1);
        unsigned b = this->locateVex(str2);
        if(a==unsigned(-1)||b==unsigned(-1)){
            cout<<"���޴˵�"<<endl;
            --i;
            continue;
        }
        graph.arcs[a][b].adj = 1;
        graph.arcs[b][a].adj = 1;
    }
}//void Graph::createGraph()

void Graph::BFS(unsigned index) {
    //���indexû��
    if (index >= graph.vexnum) return;
    //���ñ����ĵ���Ŀ
    unsigned visitNum = 0;
    //��������˳��
    queue<unsigned> Q;
    //��һ���㿪ʼ
    Q.push(index);
    visited[index] = true;
    while (visitNum < graph.vexnum) {
        //���Ϊ���һ��е�û�б��� ��ѡһ�������С��δ�����ʵĵ�
        if (Q.empty()) {
            for (unsigned i = 0; i < graph.vexnum; ++i) {
                if (!visited[i]) {
                    Q.push(i);
                    visited[i] = true;
                    break;
                }
            }
        }
        // �õ������еĵ�һ��Ԫ��
        index = Q.front();
        Q.pop();
        cout << graph.vexs[index] << " ";
        ++visitNum;
        //ѡ����˵����ڵĵ� ����
        for (unsigned i = 0; i < graph.vexnum; ++i) {
            if (graph.arcs[index][i].adj && !visited[i]) {
                Q.push(i);
                visited[i] = true;
            }
        }
    }

    //����
    for (unsigned i = 0; i < graph.vexnum; ++i) {
        visited[i] = false;
    }
}   //void Graph::BFS(unsigned index)

#endif //OJ_GRAPH_H

