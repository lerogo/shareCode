struct AVLTreeNode{
    LL data,height,num;//关键字、高度
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
//LL：左左对应的情况(左单旋转),返回旋转后的根节点
AVLTreeNode* leftLeftRotation(AVLTreeNode* k2){
    AVLTreeNode* k1= k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(getHeight(k2->left), getHeight(k2->right)) + 1;
    k1->height = max(getHeight(k1->left), k2->height) + 1;
    return k1;
}
//RR：右右对应的情况(右单旋转),返回旋转后的根节点
AVLTreeNode* rightRightRotation(AVLTreeNode* k1){
    AVLTreeNode* k2= k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max( getHeight(k1->left), getHeight(k1->right)) + 1;
    k2->height = max( getHeight(k2->right), k1->height) + 1;
    return k2;
}
//LR：左右对应的情况(左双旋转),返回旋转后的根节点
AVLTreeNode* leftRightRotation(AVLTreeNode* k3){
    k3->left = rightRightRotation(k3->left);
    return leftLeftRotation(k3);
}
//RL：右左对应的情况(右双旋转),返回旋转后的根节点
AVLTreeNode* rightLeftRotation(AVLTreeNode* k1){
    k1->right = leftLeftRotation(k1->right);
    return rightRightRotation(k1);
}
//将结点插入到AVL树中，并返回根节点
AVLTreeNode* insertNode(AVLTreeNode* &root, LL data){
    if (root == nullptr)
        root = new AVLTreeNode(data);
    else if (data < root->data){
        root->left = insertNode(root->left, data);
        // 插入节点后，若AVL树失去平衡，则进行相应的调节。
        if (getHeight(root->left) - getHeight(root->right) == 2){
            if (data < root->left->data)
                root = leftLeftRotation(root);
            else
                root = leftRightRotation(root);
        }
    }else if (data > root->data){ // 应该将data插入到"root的右子树"的情况
        root->right = insertNode(root->right, data);
        // 插入节点后，若AVL树失去平衡，则进行相应的调节。
        if (getHeight(root->right) - getHeight(root->left) == 2){
            if (data > root->right->data)
                root = rightRightRotation(root);
            else
                root = rightLeftRotation(root);
        }
    }else
        cout << "添加失败：不允许添加相同的节点！" << endl;
    root->height = max( getHeight(root->left), getHeight(root->right)) + 1;
    return root;
}
//查找最大结点：返回root为根结点的AVL树的最大结点。
AVLTreeNode* maximum(AVLTreeNode* root){
    if (root==nullptr)
        return nullptr;
    while(root->right != nullptr)
        root = root->right;
    return root;
}
//查找最小结点：返回tree为根结点的AVL树的最小结点。
AVLTreeNode* minimum(AVLTreeNode* root){
    if (root == nullptr)
        return nullptr;
    while(root->left != nullptr)
        root = root->left;
    return root;
}
//删除结点(z)，返回根节点
AVLTreeNode* remove(AVLTreeNode* &root, AVLTreeNode* z){
    // 根为空或者没有要删除的节点，直接返回nullptr。
    if (root==nullptr || z==nullptr)
        return nullptr;
    if (z->data < root->data){// 待删除的节点在"root的左子树"中
        root->left = remove(root->left, z);
        // 删除节点后，若AVL树失去平衡，则进行相应的调节。
        if (getHeight(root->right) - getHeight(root->left) == 2){
            AVLTreeNode *r =  root->right;
            if (getHeight(r->left) > getHeight(r->right))
                root = rightLeftRotation(root);
            else
                root = rightRightRotation(root);
        }
    }else if (z->data > root->data){// 待删除的节点在"root的右子树"中
        root->right = remove(root->right, z);
        // 删除节点后，若AVL树失去平衡，则进行相应的调节。
        if (getHeight(root->left) - getHeight(root->right) == 2){
            AVLTreeNode *l =  root->left;
            if (getHeight(l->right) > getHeight(l->right))
                root = leftRightRotation(root);
            else
                root = leftLeftRotation(root);
        }
    }else{    // root是对应要删除的节点。
        if ((root->left!=nullptr) && (root->right!=nullptr)){
            if (getHeight(root->left) > getHeight(root->right)){
                // 如果root的左子树比右子树高；
                // 则(01)找出root的左子树中的最大节点
                //   (02)将该最大节点的值赋值给root。
                //   (03)删除该最大节点。
                // 这类似于用"root的左子树中最大节点"做"root"的替身；
                // 采用这种方式的好处是：删除"root的左子树中最大节点"之后，AVL树仍然是平衡的。
                AVLTreeNode* Max = maximum(root->left);
                root->data = Max->data;
                root->left = remove(root->left, Max);
            }else{
                // 如果root的左子树不比右子树高(即它们相等，或右子树比左子树高1)
                // 则(01)找出root的右子树中的最小节点
                //   (02)将该最小节点的值赋值给root。
                //   (03)删除该最小节点。
                // 这类似于用"root的右子树中最小节点"做"root"的替身；
                // 采用这种方式的好处是：删除"root的右子树中最小节点"之后，AVL树仍然是平衡的。
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
