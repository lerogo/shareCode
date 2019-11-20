//ans中存储后根遍历序列
vector<LL> ans;
vector<LL> postorderTraversal(TreeNode* root) {
    stack<TreeNode*> st;
    while (!st.empty() || root != nullptr) {
        for (; root != nullptr; root = root->right) {
            ans.push_back(root->val);
            st.push(root);
        }
        root = st.top()->left;
        st.pop();
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
