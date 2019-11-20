//�����������в��ҵ�һ������ĳ������λ�ã���������Ϊ����ұյ�����[left,right]��fΪҪ���������
LL solve(vector<LL>& v, LL left, LL right, function<bool(LL)> f) {
    while (left <= right) {
        if (left == right)
            return f(left) ? left : left + 1;
        LL mid = left + (right - left) / 2;
        if (f(mid))
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}
