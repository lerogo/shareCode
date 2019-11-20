//调用subsets函数生成所有子集,子集存储在ans中
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
