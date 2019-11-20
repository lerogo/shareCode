TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    return (root->val - p->val) * (root->val - q->val) < 1 ? root : lowestCommonAncestor(p->val < root->val ? root->left : root->right, p, q);
}
