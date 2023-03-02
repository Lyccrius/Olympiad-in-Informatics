#include <iostream>
#include <algorithm>
#include <cmath>

typedef long long lxl;

const int maxN = 60;
const lxl inf = 1e16;

lxl x[maxN + 10];
lxl y[maxN + 10];
lxl ax, ay, bx, by;
lxl xs, ys, t;
lxl ans;

lxl dis(lxl x1, lxl y1, lxl x2, lxl y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

int main() {
    std::cin >> x[0] >> y[0] >> ax >> ay >> bx >> by;
    std::cin >> xs >> ys >> t;
    int lim = maxN;
    for (int i = 1; i <= maxN; i++) {
        x[i] = ax * x[i - 1] + bx;
        y[i] = ay * y[i - 1] + by;
        if (x[i] > inf || y[i] > inf) {
            lim = i;
            break;
        }
    }
    for (int i = 0; i <= lim; i++) {
        lxl T = t;
        lxl res = 0;
        lxl now = i;
        lxl xn = xs;
        lxl yn = ys;
        while (now >= 0) {
            if (T >= dis(x[now], y[now], xn, yn)) {
                T -= dis(x[now], y[now], xn, yn);
                //std::cout << now << ' ' << '(' << x[now] << ',' << y[now] << ')' << '\n';
                xn = x[now];
                yn = y[now];
                res++;
                now--;
            } else {
                break;
            }
        }
        now = i + 1;
        while (now <= lim) {
            if (T >= dis(x[now], y[now], xn, yn)) {
                //std::cout << now << ' ' << '(' << x[now] << ',' << y[now] << ')' << '\n';
                T -= dis(x[now], y[now], xn, yn);
                xn = x[now];
                yn = y[now];
                res++;
                now++;
            } else {
                break;
            }
        }
        ans = std::max(ans, res);
    }
    std::cout << ans;
    return 0;
}