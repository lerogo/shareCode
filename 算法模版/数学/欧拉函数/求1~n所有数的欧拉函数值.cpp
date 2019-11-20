void phi_table(LL n, vector<LL>&phi) {
    for(LL i = 2; i <= n; i++) 
        phi[i] = 0;
    phi[1] = 1;
    for(LL i = 2; i <= n; i++) 
        if(phi[i]==0)
            for(LL j = i; j <= n; j += i) {
                if(phi[j]==0) 
                    phi[j] = j;
                phi[j] = phi[j] / i * (i-1);
            }
}
