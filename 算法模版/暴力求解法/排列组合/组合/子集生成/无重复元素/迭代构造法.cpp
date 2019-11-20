//调用subsets函数生成所有子集,子集存储在ans中
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
