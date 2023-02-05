#include <iostream>
#include <algorithm>

const int maxN = 1e4;
const double inf = 1e9;
const double eps = 1e-9;

int T;
int n;
double a[maxN + 10], b[maxN + 10], c[maxN + 10];

double f(double x, int i) {
    //printf("f(%lf, %d) = %lf\n", x, i, a[i] * x * x + b[i] * x + c[i]);
    return a[i] * x * x + b[i] * x + c[i];
}

double check(double x) {
    double ret = -inf;
    for (int i = 1; i <= n; i++) ret = std::max(ret, f(x, i));
    //printf("check(%lf) = %lf\n", x, ret);
    return ret;
}

void mian() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i] >> b[i] >> c[i];
    double l = 0;
    double r = 1000;
    while (r - l >= eps) {
        double gap = (r - l) / 3;
        double lmid = l + gap;
        double rmid = r - gap;
        if (check(lmid) > check(rmid)) l = lmid;
        else r = rmid;
    }
    printf("%.4lf\n", check(l));
    return;
}

int main() {
    std::cin >> T;
    while (T--) mian();
    return 0;
}