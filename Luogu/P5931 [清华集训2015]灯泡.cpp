#include <iostream>

const int maxT = 100;
const double eps = 1e-10;

int T;
double H, h, D;

double f(double x) {
    double d = (h * x) / (H - h);
    double L;
    if (x + d <= D) {
        L = d;
    } else {
        double l = (h / d) * (x + d - D);
        L = (D - x) + l;
    }
    return L;
}

void mian() {
    std::cin >> H >> h >> D;
    double l = 0;
    double r = D;
    while (r - l >= eps) {
        double gap = (r - l) / 3;
        double lmid = l + gap;
        double rmid = r - gap;
        if (f(lmid) < f(rmid)) l = lmid;
        else r = rmid;
    }
    printf("%.3lf\n", f(l));
    return;
}

int main() {
    std::cin >> T;
    while (T--) mian();
    return 0;
}