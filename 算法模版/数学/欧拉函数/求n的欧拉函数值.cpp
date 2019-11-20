LL euler_phi(LL n) {
    LL m = (LL)sqrt(n+0.5),ans = n;
    for(LL i = 2; i <= m; i++) 
        if(n % i == 0) {
            ans = ans / i * (i-1);
            while(n % i == 0) 
                n /= i;
        }
    if(n > 1) 
        ans = ans / n * (n-1);
    return ans;
}
