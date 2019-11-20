void combine(LL n, LL k) {
    LL i = 0;
    vector<LL> p(k, 0);
    while (i >= 0) {
        p[i]++;
        if (p[i] > n)
            --i;
        else if (i == k - 1) {
            //处理当前组合
        } else {
            ++i;
            p[i] = p[i - 1];
        }
    }
}
