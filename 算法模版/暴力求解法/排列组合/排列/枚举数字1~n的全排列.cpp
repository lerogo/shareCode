void f(vector<LL>& A, LL n) {
    if (A.size() == n) {  //递归边界
        for (LL i = 0; i < A.size(); i++) prLLf("%d ", A[i]);
        prLLf("\n");
        return;
    }
    for (LL i = 1; i <= n; i++) {  //尝试在A末尾填各种整数i
        if (find(A.begin(), A.end(), i) != A.end())
            continue;
        A.push_back(i);
        f(A, n);  //递归调用
        A.pop_back();
    }
}
