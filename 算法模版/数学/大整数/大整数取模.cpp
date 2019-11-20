//输出n%m的值，其中n<=10^10,m<=10^9
long long bigIntegerMod(const string& n, long long m) {
    long long ans = 0;
    for (LL i = 0; i < n.size(); ++i)
        ans = ((ans * 10 + n[i] - '0') % m);
    return ans;
}
