//ans中存储每一层的层次遍历序列
vector<vector<LL>> ans;
vector<vector<LL>> levelOrder(TreeNode* root) {
    if (root == nullptr)
        return {};
    queue<TreeNode*> q;
    q.push(root);
    vector<vector<LL>> ans;
    while (!q.empty()) {
        LL k = q.size();
        ans.push_back({});
        while (k--) {
            auto i = q.front();
            q.pop();
            ans.back().push_back(i->val);
            if (i->left != nullptr)
                q.push(i->left);
            if (i->right != nullptr)
                q.push(i->right);
        }
    }
    return ans;
}
