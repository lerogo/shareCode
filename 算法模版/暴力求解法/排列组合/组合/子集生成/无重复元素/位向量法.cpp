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
    bits[i] = true;
    f(nums, bits, i + 1);
    bits[i] = false;
    f(nums, bits, i + 1);
}
void subsets(vector<LL>& nums) {
    bitset<100> bits;
    f(nums, bits, 0);
}
