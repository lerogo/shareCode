LL gcd(LL a,LL b){
    return b==0?a:gcd(b,a%b);
}
