//调用f(A,0)，如果要求字典序输出全排列，调用之前请先对A排序
void f(vector<LL>& A, LL index) {
    if (index == A.size()) {
        //处理当前的排列
        return;
    }
    for (LL i = index; i < A.size(); ++i) {
        swap(A[index], A[i]);
        f(A, index + 1);
        swap(A[index], A[i]);
    }
}
