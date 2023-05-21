#include <iostream>
#include <iomanip>
#include <cmath>

typedef long double dbl;

const int maxN = 1000;
const dbl eps = 1e-20;
const dbl del = 0.996;

int n;
dbl x[maxN + 10], y[maxN + 10], w[maxN + 10];
dbl ansx, ansy, answ;

dbl energy(dbl tx, dbl ty) {
    dbl ret = 0;
    for (int i = 1; i <= n; i++) {
        dbl dx = tx - x[i];
        dbl dy = ty - y[i];
        ret += sqrt(dx * dx + dy * dy) * w[i];
    }
    return ret;
}

void SimulatedAnnealing() {
    srand(time(0));
    srand(rand());
    dbl t = 30000;
    while (t >= eps) {
        dbl tx = ansx + (rand() * 2 - RAND_MAX) * t;
        dbl ty = ansy + (rand() * 2 - RAND_MAX) * t;
        dbl tw = energy(tx, ty);
        dbl dw = answ - tw;
        if (dw > 0) {
            ansx = tx;
            ansy = ty;
            answ = tw;
        } else if (exp(dw / t) > rand()) {
            ansx = tx;
            ansy = ty;
            answ = tw;
        }
        t *= del;
    }
    return;
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> x[i] >> y[i] >> w[i];
    for (int i = 1; i <= n; i++) ansx += x[i];
    for (int i = 1; i <= n; i++) ansy += y[i];
    ansx /= n;
    ansy /= n;
    answ = energy(ansx, ansy);
    SimulatedAnnealing();
    std::cout << std::setiosflags(std::ios::fixed);
    std::cout << std::setprecision(3) << ansx << ' ' << ansy << '\n';
    return 0;
}