void f(vector<LL>& A, LL n) {
    if (A.size() == n) {  //�ݹ�߽�
        for (LL i = 0; i < A.size(); i++) prLLf("%d ", A[i]);
        prLLf("\n");
        return;
    }
    for (LL i = 1; i <= n; i++) {  //������Aĩβ���������i
        if (find(A.begin(), A.end(), i) != A.end())
            continue;
        A.push_back(i);
        f(A, n);  //�ݹ����
        A.pop_back();
    }
}
