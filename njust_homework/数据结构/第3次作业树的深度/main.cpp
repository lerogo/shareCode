#include <iostream>

using namespace std;

//���������� ʹ�ö�������
class BTree {
	public:
		int val;    //�ڵ��
		BTree *l, *r;   //��������

		//��ʼ��
		BTree() {
			this->l = nullptr;
			this->r = nullptr;
		}
		//�ͷ�
		~BTree() {
			BTreeDestroy();
		}
		int BTreeDepth();       //�������
		void BTreeDestroy();    //���� �ͷſռ�
		static BTree *buildTree(int ind, int **treeData);   //������
};

int main() {
	unsigned n;
	cin >> n;
	// �������� �� �� ���ݣ�treeData��
	int **treeData = new int *[n + 10];
	for (unsigned i = 1; i <= n; ++i) {
		treeData[i] = new int[2];
	}
	//����
	for (unsigned i = 1; i <= n; ++i) {
		cin >> treeData[i][0] >> treeData[i][1];
	}
	// ������
	BTree *root = BTree::buildTree(1, treeData);

	//������
//    cout << "�������̣�";
	int re = root->BTreeDepth();
//    cout << endl << "���Ϊ��";
	cout << re<<endl;

	system("pause");
	return 0;
}

BTree *BTree::buildTree(int ind, int **treeData) {
	if (ind == -1) return nullptr;

	//�����ڵ�
	BTree *root = new BTree;
	root->val = ind;
	//����������
	BTree *l = buildTree(treeData[ind][0], treeData);
	root->l = l;
	//����������
	BTree *r = buildTree(treeData[ind][1], treeData);
	root->r = r;

	return root;
}

int BTree::BTreeDepth() {
	if (this == nullptr) return 0;
//	cout << this->val << " ";
	//�ݹ���������
	int cnt_l = this->l->BTreeDepth();
	//�ݹ���������
	int cnt_r = this->r->BTreeDepth();
	//�Ƚ�����
	return cnt_l > cnt_r ? cnt_l + 1 : cnt_r + 1;
}

void BTree::BTreeDestroy() {
	if (this == nullptr) return;
	this->l->BTreeDepth();
	this->r->BTreeDepth();
	delete this;
}
