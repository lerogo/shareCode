vector<LL> trans10toR(LL i, LL R) {
    vector<LL> ans;
    do {
        ans.push_back(i % R);
        i /= R;
    } while (i != 0);
    reverse(ans.begin(), ans.end());
    return ans;
}
