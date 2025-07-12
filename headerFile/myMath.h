#ifndef MATH_H
#define MATH_H

#define fabs(a) ((a)>0?(a):(-(a)))

double F1(double x) {
	return 1 / x;
}

double simpson(double a, double b) {
	double c = a + (b - a) / 2;
	return (F1(a) + 4 * F1(c) + F1(b)) * (b - a) / 6;
}

double asr(double a, double b, double eps, double A) {
	double c = a + (b - a) / 2;
	double L = simpson(a, c), R = simpson(c, b);
	if (fabs(L + R - A) <= 15 * eps) return L + R + (L + R - A) / 15.0;
	return asr(a, c, eps / 2, L) + asr(c, b, eps / 2, R);
}

double asrr(double a, double b, double eps) {
	return asr(a, b, eps, simpson(a, b));
}

double ln(double x) {
	return asrr(1, x, 1e-8);
}

double Log2(double x) {
	return ln(x)/ln(2);
}

int Pow(int a, int n) {
    int res = 1;
    while(n)
    {
        if(n&1) res *= a;
        a *= a;
        n >>= 1;
    }
    return res;
}

#endif
