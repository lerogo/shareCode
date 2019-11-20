LL transRto10(const vector<LL>& r, LL R) {
    LL d = 0;
    for (LL i : r)
        d = d * R + i;
    return d;
}
