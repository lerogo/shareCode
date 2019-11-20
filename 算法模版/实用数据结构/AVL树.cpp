struct AVLTreeNode{
    LL data,height,num;//�ؼ��֡��߶�
    AVLTreeNode *left,*right;
    AVLTreeNode(LL value, AVLTreeNode *l=nullptr, AVLTreeNode *r=nullptr):data(value), height(0),left(l),right(r) {}
};
LL getHeight(AVLTreeNode*r){
    return r==nullptr?0:r->height;
}
AVLTreeNode*findAVL(AVLTreeNode*root,LL data){
    if (root==nullptr || root->data==data)
        return root;
    if (data < root->data)
        return findAVL(root->left, data);
    else
        return findAVL(root->right, data);
}
//LL�������Ӧ�����(����ת),������ת��ĸ��ڵ�
AVLTreeNode* leftLeftRotation(AVLTreeNode* k2){
    AVLTreeNode* k1= k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(getHeight(k2->left), getHeight(k2->right)) + 1;
    k1->height = max(getHeight(k1->left), k2->height) + 1;
    return k1;
}
//RR�����Ҷ�Ӧ�����(�ҵ���ת),������ת��ĸ��ڵ�
AVLTreeNode* rightRightRotation(AVLTreeNode* k1){
    AVLTreeNode* k2= k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max( getHeight(k1->left), getHeight(k1->right)) + 1;
    k2->height = max( getHeight(k2->right), k1->height) + 1;
    return k2;
}
//LR�����Ҷ�Ӧ�����(��˫��ת),������ת��ĸ��ڵ�
AVLTreeNode* leftRightRotation(AVLTreeNode* k3){
    k3->left = rightRightRotation(k3->left);
    return leftLeftRotation(k3);
}
//RL�������Ӧ�����(��˫��ת),������ת��ĸ��ڵ�
AVLTreeNode* rightLeftRotation(AVLTreeNode* k1){
    k1->right = leftLeftRotation(k1->right);
    return rightRightRotation(k1);
}
//�������뵽AVL���У������ظ��ڵ�
AVLTreeNode* insertNode(AVLTreeNode* &root, LL data){
    if (root == nullptr)
        root = new AVLTreeNode(data);
    else if (data < root->data){
        root->left = insertNode(root->left, data);
        // ����ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
        if (getHeight(root->left) - getHeight(root->right) == 2){
            if (data < root->left->data)
                root = leftLeftRotation(root);
            else
                root = leftRightRotation(root);
        }
    }else if (data > root->data){ // Ӧ�ý�data���뵽"root��������"�����
        root->right = insertNode(root->right, data);
        // ����ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
        if (getHeight(root->right) - getHeight(root->left) == 2){
            if (data > root->right->data)
                root = rightRightRotation(root);
            else
                root = rightLeftRotation(root);
        }
    }else
        cout << "���ʧ�ܣ������������ͬ�Ľڵ㣡" << endl;
    root->height = max( getHeight(root->left), getHeight(root->right)) + 1;
    return root;
}
//��������㣺����rootΪ������AVL��������㡣
AVLTreeNode* maximum(AVLTreeNode* root){
    if (root==nullptr)
        return nullptr;
    while(root->right != nullptr)
        root = root->right;
    return root;
}
//������С��㣺����treeΪ������AVL������С��㡣
AVLTreeNode* minimum(AVLTreeNode* root){
    if (root == nullptr)
        return nullptr;
    while(root->left != nullptr)
        root = root->left;
    return root;
}
//ɾ�����(z)�����ظ��ڵ�
AVLTreeNode* remove(AVLTreeNode* &root, AVLTreeNode* z){
    // ��Ϊ�ջ���û��Ҫɾ���Ľڵ㣬ֱ�ӷ���nullptr��
    if (root==nullptr || z==nullptr)
        return nullptr;
    if (z->data < root->data){// ��ɾ���Ľڵ���"root��������"��
        root->left = remove(root->left, z);
        // ɾ���ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
        if (getHeight(root->right) - getHeight(root->left) == 2){
            AVLTreeNode *r =  root->right;
            if (getHeight(r->left) > getHeight(r->right))
                root = rightLeftRotation(root);
            else
                root = rightRightRotation(root);
        }
    }else if (z->data > root->data){// ��ɾ���Ľڵ���"root��������"��
        root->right = remove(root->right, z);
        // ɾ���ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
        if (getHeight(root->left) - getHeight(root->right) == 2){
            AVLTreeNode *l =  root->left;
            if (getHeight(l->right) > getHeight(l->right))
                root = leftRightRotation(root);
            else
                root = leftLeftRotation(root);
        }
    }else{    // root�Ƕ�ӦҪɾ���Ľڵ㡣
        if ((root->left!=nullptr) && (root->right!=nullptr)){
            if (getHeight(root->left) > getHeight(root->right)){
                // ���root�����������������ߣ�
                // ��(01)�ҳ�root���������е����ڵ�
                //   (02)�������ڵ��ֵ��ֵ��root��
                //   (03)ɾ�������ڵ㡣
                // ����������"root�������������ڵ�"��"root"������
                // �������ַ�ʽ�ĺô��ǣ�ɾ��"root�������������ڵ�"֮��AVL����Ȼ��ƽ��ġ�
                AVLTreeNode* Max = maximum(root->left);
                root->data = Max->data;
                root->left = remove(root->left, Max);
            }else{
                // ���root��������������������(��������ȣ�������������������1)
                // ��(01)�ҳ�root���������е���С�ڵ�
                //   (02)������С�ڵ��ֵ��ֵ��root��
                //   (03)ɾ������С�ڵ㡣
                // ����������"root������������С�ڵ�"��"root"������
                // �������ַ�ʽ�ĺô��ǣ�ɾ��"root������������С�ڵ�"֮��AVL����Ȼ��ƽ��ġ�
                AVLTreeNode* Min = minimum(root->right);
                root->data = Min->data;
                root->right = remove(root->right, Min);
            }
        }else{
            AVLTreeNode* tmp = root;
            root = (root->left!=nullptr) ? root->left : root->right;
            delete tmp;
        }
    }
    return root;
}
void remove(AVLTreeNode* &root,LL data){
    AVLTreeNode* z;
    if ((z = findAVL(root, data)) != nullptr)
        root = remove(root, z);
}
