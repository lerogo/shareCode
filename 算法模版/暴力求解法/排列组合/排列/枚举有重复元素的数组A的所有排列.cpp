//����drive(A),���Ҫ���ֵ������ȫ���У���ʹ��map���� unordered_map
void permute(vector<LL> &v, LL index, unordered_map<LL, LL> &um) {
    if (index <= 0) {
        //����ǰ������
        return;
    }
    for (auto &i : um) {
        if (i.second <= 0)
            continue;
        --i.second;
        v.push_back(i.first);
        permute(v, index - 1, um);
        v.pop_back();
        ++i.second;
    }
}
void drive(vector<LL> &A) {
    unordered_map<LL, LL> um;
    for (LL i : A)
        ++um[i];
    vector<LL> v;
    permute(v, A.size(), um);
}
