bool isPrime(LL n) {
    if (n < 2)
        return false;
    for (LL i = 2; i <= (LL)sqrt(n * 1.0); ++i)
        if (n % i == 0)
            return false;
    return true;
}