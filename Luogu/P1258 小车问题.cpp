#include <iostream>
#include <cmath>

const double eps = 1e-6;

double s, a, b;

bool check(double x) {
    double t11 = x / b;
    double t12 = (s - x) / a;
    double t1 = t11 + t12;
    double s21 = a * t11;
    double t21 = (x - s21) / (a + b);
    double s22 = a * t21;
    double t22 = (s - s21 - s22) / b;
    double t2 = t11 + t21 + t22;
    //printf("checking %lf\n", x);
    //printf("t1 = %lf, t2 = %lf\n", t1, t2);
    return t1 <= t2;
}

int main() {
    std::cin >> s >> a >> b;
    double l = 0;
    double r = s;
    while (r - l >= eps) {
        double mid = (l + r) / 2;
        if (check(mid)) r = mid;
        else l = mid;
    }
    double t1 = l / b;
    double t2 = (s - l) / a;
    double t = t1 + t2;
    //std::cout << t;
    printf("%lf", t);
    return 0;
}