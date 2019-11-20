//需要保证n>=0，如果指数小于0，取绝对值传参，再对函数f的计算结果取倒数
double f(double x, LL n) {
    if (n == 0)
        return 1;
    return (n % 2 == 0) ? pow(x * x, n / 2) : x * pow(x * x, n / 2);
}
