struct Node {
    LL left = -1, right = -1, sum = 0;
};
vector<Node> tree(n << 1);  //nΪԭ���������ֵĸ���
LL getIndex(LL i) {  //������A���±�iת���ɶ�Ӧ��tree�е��±�
    LL n = tree.size() >> 1, k = (1 << (LL)log2(n + n - 1)) - n;
    return (n + i - 1 + k) % n + n;
}
void createTree(vector<LL>& A) {  //����
    LL n = tree.size() >> 1;
    for (LL i = 1; i <= n; ++i) {
        LL p = getIndex(i);
        tree[p].left = tree[p].right = i;
        tree[p].sum = A[i];
    }
    for (LL i = n - 1; i > 0; --i) {
        tree[i].left = min(tree[i << 1].left, tree[(i << 1) + 1].left);
        tree[i].right = max(tree[i << 1].right, tree[(i << 1) + 1].right);
        tree[i].sum = tree[i << 1].sum + tree[(i << 1) + 1].sum;
    }
}
void update(LL p, LL v) {  //��A[p]����v
    for (LL i = getIndex(p); i > 0; i >>= 1)
        tree[i].sum += v;
}
LL query(LL root, LL left, LL right) {  //��ѯA��[left,right]����ĺ�
    if (tree[root].left >= left && tree[root].right <= right)
        return tree[root].sum;
    LL sum = 0, mid = tree[root].left + (tree[root].right - tree[root].left) / 2;
    LL child = root << 1;
    if (child < tree.size() && left <= mid)
        sum += query(child, left, right);
    if (child + 1 < tree.size() && right > mid)
        sum += query(child + 1, left, right);
    return sum;
}
