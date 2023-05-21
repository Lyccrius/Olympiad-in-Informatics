#include <iostream>
#include <cmath>

typedef double dbl;
typedef long long lxl;

const int maxT = 20;
const int maxN = 30;
const lxl maxV = 1ll << 30;
const dbl eps = 1e-15;
const dbl del = 0.996;

int t;
int n;
int v[maxN + 10];
lxl ans;

int range(int l, int r) {
    int len = (r - l + 1);
    int ret = rand() % len;
    return ret + l;
}

int calc() {
    int mid = n / 2;
    lxl a = 0;
    lxl b = 0;
    for (int i = 1; i <= mid; i++) a += v[i];
    for (int i = mid + 1; i <= n; i++) b += v[i];
    return std::abs(a - b);
}

void SimulatedAnnealing() {
    dbl t = 300000;
    while (t >= eps) {
        int mid = n / 2;
        int x = range(1, mid);
        int y = range(mid + 1, n);
        std::swap(v[x], v[y]);
        lxl res = calc();
        if (ans > res) {
            ans = res;
        } else if (exp(1.0 * (ans - res) / t) < 1.0 * rand() / RAND_MAX) std::swap(v[x], v[y]);
        t *= del;
    }
    return;
}

void mian() {
    ans = 1ll * maxN * maxV;
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> v[i];
    if (n == 1) {
        std::cout << v[n] << '\n';
        return;
    }
    for (int i = 1; i <= 20; i++) SimulatedAnnealing();
    std::cout << ans << '\n';
    return;
}

int main() {
    srand(time(0));
    std::cin >> t;
    while (t--) mian();
    return 0;
}