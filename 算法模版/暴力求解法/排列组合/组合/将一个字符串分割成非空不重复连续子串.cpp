//����f�����������зָ��Ӵ�,�ָ��Ӵ��洢��ans��
vector<vector<string>> ans;
vector<string> temp;
void f(string& s, LL i) {
    if (i == s.size()) {
        ans.push_back(temp);
        return;
    }
    for (LL j = i; j < s.size(); ++j) {
        if (p[i * s.size() + j]) {
            temp.push_back(s.substr(i, j - i + 1));
            f(s, j + 1);
            temp.pop_back();
        }
    }
}
