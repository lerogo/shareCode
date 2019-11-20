//��������Ľṹ�嶨��
struct F {
    LL son, mother;  //����,��ĸ
    F(LL s, LL m) : son(s), mother(m) {}
};
//����������Ϊ������
void simplify(F& f) {
    if (f.son == 0) {  //����Ϊ0����ĸ����Ϊ1
        f.mother = 1;
        return;
    }
    if (f.mother < 0) {  //�ѷ�ĸ�ϵĸ����Ƶ�������
        f.son = -f.son;
        f.mother = -f.mother;
    }
    LL d = gcd(abs(f.son), f.mother);  //����ӷ�ĸ���Լ��
    f.son /= d;
    f.mother /= d;
}
//�������
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
