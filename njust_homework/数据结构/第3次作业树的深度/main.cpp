#include <iostream>

using namespace std;

//如果仅求深度 使用二叉链表
class BTree {
	public:
		int val;    //节点号
		BTree *l, *r;   //左右子树

		//初始化
		BTree() {
			this->l = nullptr;
			this->r = nullptr;
		}
		//释放
		~BTree() {
			BTreeDestroy();
		}
		int BTreeDepth();       //求树深度
		void BTreeDestroy();    //销毁 释放空间
		static BTree *buildTree(int ind, int **treeData);   //建立树
};

int main() {
	unsigned n;
	cin >> n;
	// 存放输入的 树 的 数据（treeData）
	int **treeData = new int *[n + 10];
	for (unsigned i = 1; i <= n; ++i) {
		treeData[i] = new int[2];
	}
	//输入
	for (unsigned i = 1; i <= n; ++i) {
		cin >> treeData[i][0] >> treeData[i][1];
	}
	// 建立树
	BTree *root = BTree::buildTree(1, treeData);

	//求解深度
//    cout << "遍历过程：";
	int re = root->BTreeDepth();
//    cout << endl << "深度为：";
	cout << re<<endl;

	system("pause");
	return 0;
}

BTree *BTree::buildTree(int ind, int **treeData) {
	if (ind == -1) return nullptr;

	//建立节点
	BTree *root = new BTree;
	root->val = ind;
	//建立左子树
	BTree *l = buildTree(treeData[ind][0], treeData);
	root->l = l;
	//建立右子树
	BTree *r = buildTree(treeData[ind][1], treeData);
	root->r = r;

	return root;
}

int BTree::BTreeDepth() {
	if (this == nullptr) return 0;
//	cout << this->val << " ";
	//递归求左子树
	int cnt_l = this->l->BTreeDepth();
	//递归求右子树
	int cnt_r = this->r->BTreeDepth();
	//比较左右
	return cnt_l > cnt_r ? cnt_l + 1 : cnt_r + 1;
}

void BTree::BTreeDestroy() {
	if (this == nullptr) return;
	this->l->BTreeDepth();
	this->r->BTreeDepth();
	delete this;
}
