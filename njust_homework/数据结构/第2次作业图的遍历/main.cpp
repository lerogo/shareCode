#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
    //freopen("./in.txt", "r", stdin);

    // ʹ�� �ڽӾ��� �� ����ͼ ���� ��ȱ���
    Graph g1;
    g1.createGraph();
    cout<<"���������"<<endl;
    g1.BFS(0);  //��ȱ���  �ǵݹ����
	cout<<endl;
	system("pause");
    return 0;
}


