//����subsets�������������Ӽ�,�Ӽ��洢��ans��
//bitset�ĳ�����Ҫ��nums����󳤶ȴ������100Ҫ����ĿҪ��仯
vector<vector<LL>> ans;
void f(vector<LL>& nums, bitset<100>& bits, LL i) {
    if (i == nums.size()) {
        ans.push_back({});
        for (LL i = 0; i < nums.size(); ++i)
            if (bits[i]) {
                ans.back().push_back(nums[i]);
            }
        return;
    }
    LL j = find_if(nums.begin() + i, nums.end(), [i, &nums](LL a) {
                return a != nums[i];
            }) - nums.begin();
    for (LL k = i; k < j; ++k) {
        bits[k] = true;
        f(nums, bits, j);
    }
    for (LL k = i; k < j; ++k)
        bits[k] = false;
    f(nums, bits, j);
}
void subsetsWithDup(vector<LL>& nums) {
    sort(nums.begin(), nums.end());
    bitset<100> bits;
    f(nums, bits, 0);
}
