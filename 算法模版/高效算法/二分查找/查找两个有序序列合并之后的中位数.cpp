double findMedianSortedArrays(vector<LL>& nums1, vector<LL>& nums2) {
    LL m = nums1.size(), n = nums2.size();
    if (m > n)
        return findMedianSortedArrays(nums2, nums1);
    for (LL left = 0, right = m; left <= right;) {
        LL i = left + (right - left) / 2, j = (m + n + 1) / 2 - i;
        LL max1 = i >= 1 ? nums1[i - 1] : LONG_LONG_MIN, max2 = j >= 1 ? nums2[j - 1] : LONG_LONG_MIN;
        LL min1 = i < m ? nums1[i] : LONG_LONG_MAX, min2 = j < n ? nums2[j] : LONG_LONG_MAX;
        if (min1 >= max2 && max1 <= min2) {
            return (m + n) % 2 == 1 ? max(max1, max2) * 1.0 : (max(max1, max2) + min(min1, min2)) / 2.0;
        } else if (min1 < max2) {
            left = i + 1;
        } else
            right = i - 1;
    }
    return LONG_LONG_MIN * 1.0;  //没有找到中位数
}
