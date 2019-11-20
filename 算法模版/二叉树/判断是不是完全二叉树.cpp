bool isCompleteTree(TreeNode* root) {
    queue<pair<TreeNode*, LL>> q;
    q.push({root, 1});
    for (LL last = 1; !q.empty(); ++last) {
        auto i = q.front();
        q.pop();
        if (last != i.second)
            return false;
        if (i.first->left != nullptr)
            q.push({i.first->left, i.second * 2});
        if (i.first->right != nullptr)
            q.push({i.first->right, i.second * 2 + 1});
    }
    return true;
}
