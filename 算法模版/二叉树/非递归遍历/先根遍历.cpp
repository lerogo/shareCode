//ans�д洢�ȸ���������
vector<LL> ans;
vector<LL> preorderTraversal(TreeNode* root) {
    stack<TreeNode*> st;
    while (!st.empty() || root != nullptr) {
        for (; root != nullptr; root = root->left) {
            ans.push_back(root->val);
            st.push(root);
        }
        root = st.top()->right;
        st.pop();
    }
    return ans;
}
