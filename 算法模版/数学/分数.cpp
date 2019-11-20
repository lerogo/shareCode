//储存分数的结构体定义
struct F {
    LL son, mother;  //分子,分母
    F(LL s, LL m) : son(s), mother(m) {}
};
//将分数化简为最简分数
void simplify(F& f) {
    if (f.son == 0) {  //分子为0，分母均变为1
        f.mother = 1;
        return;
    }
    if (f.mother < 0) {  //把分母上的负号移到分子上
        f.son = -f.son;
        f.mother = -f.mother;
    }
    LL d = gcd(abs(f.son), f.mother);  //求分子分母最大公约数
    f.son /= d;
    f.mother /= d;
}
//分数输出
void output(Fraction& f) {
    if (f.mother == 1)
        printf("%lld", f.son);
    else {
        if (abs(f.son) < f.mother)
            printf("%lld/%lld", f.son, f.mother);
        else
            printf("%lld %lld/%lld", f.son / f.mother, abs(f.son) % f.mother, f.mother);
    }
}
