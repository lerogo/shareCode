//����subsets�������������Ӽ�,�Ӽ��洢��ans��
vector<vector<LL>> ans;
void subsets(vector<LL>& nums) {
    LL n = nums.size();
    ans.resize(1 << n);
    for (LL i = 0; i < (1 << n); ++i)
        for (LL j = 0; j < n; ++j)
            if ((i >> j) & 1) {
                ans[i].push_back(nums[j]);
            }
}
