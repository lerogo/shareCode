//����f(A,0)�����Ҫ���ֵ������ȫ���У�����֮ǰ���ȶ�A����
void f(vector<LL>& A, LL index) {
    if (index == A.size()) {
        //����ǰ������
        return;
    }
    for (LL i = index; i < A.size(); ++i) {
        swap(A[index], A[i]);
        f(A, index + 1);
        swap(A[index], A[i]);
    }
}
