//����subsets�������������Ӽ�,�Ӽ��洢��ans��
vector<vector<LL>> ans;
void subsets(vector<LL>& nums) {
    ans.push_back({});
    for (LL n : nums) {
        for (LL i = 0, s = ans.size(); i < s; ++i) {
            ans.push_back(ans[i]);
            ans.back().push_back(n);
        }
    }
}
