//��Ҫ��֤n>=0�����ָ��С��0��ȡ����ֵ���Σ��ٶԺ���f�ļ�����ȡ����
double f(double x, LL n) {
    if (n == 0)
        return 1;
    return (n % 2 == 0) ? pow(x * x, n / 2) : x * pow(x * x, n / 2);
}
