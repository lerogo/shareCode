auto lowbit = [](LL x) { return x & (-x); };
vector<LL> c(MAX);
void update(LL x, LL v) {
    for (LL i = x; i < c.size(); i += lowbit(i))
        c[i] += v;
}
LL getSum(LL x) {
    LL sum = 0;
    for (LL i = x; i > 0; i -= lowbit(i))
        sum += c[i];
    return sum;
}
