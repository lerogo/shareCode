//划分算法，将数组nums分成<t、==t、>t三部分
void partition(vector<LL>& nums, LL t) {
    for (LL i = 0, j = 0, k = nums.size() - 1; i <= k;) {
        if (nums[i] > t)
            swap(nums[i], nums[k--]);
        else if (nums[i] < t)
            swap(nums[i++], nums[j++]);
        else
            ++i;
    }
}
