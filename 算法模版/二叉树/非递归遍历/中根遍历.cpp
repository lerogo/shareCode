//ans中存储中根遍历序列
vector<LL> ans;
vector<LL> inorderTraversal(TreeNode* root) {
    stack<TreeNode*> st;
    while (!st.empty() || root != nullptr) {
        for (; root != nullptr; root = root->left)
            st.push(root);
        root = st.top();
        st.pop();
        ans.push_back(root->val);
        root = root->right;
    }
    return ans;
}
