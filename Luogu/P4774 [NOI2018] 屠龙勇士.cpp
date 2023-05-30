#include <iostream>
#include <set>

typedef long long lxl;
typedef __int128 i28;
typedef std::multiset<lxl> mit;

const int maxN = 1e5;
const int maxM = 1e5;

int T;
int n, m;
lxl a[maxN + 10];
lxl p[maxN + 10];
lxl r[maxN + 10];
lxl t[maxM + 10];
mit s;

lxl exgcd(lxl a, lxl &x, lxl b, lxl &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    lxl d = exgcd(b, y, a % b, x);
    y -= a / b * x;
    return d;
}

namespace excrt {
    lxl a[maxN + 10];
    lxl b[maxN + 10];
    lxl m[maxN + 10];
    lxl x;
    lxl M;
    lxl L;

    lxl solve() {
        x = 0;
        M = 1;
        L = 0;
        for (int i = 1; i <= n; i++) L = std::max(L, (a[i] - 1) / b[i] + 1);
        for (int i = 1; i <= n; i++) {
            lxl p, q;
            lxl d = (a[i] - (i28) b[i] * x % m[i] + m[i]) % m[i];
            lxl g = exgcd((i28) b[i] * M % m[i], p, m[i], q);
            p = ((i28) p * (d / g)) % (m[i] / g);
            p = (p + m[i] / g) % (m[i] / g);
            if (d % g) return -1;
            x = (i28) x + (i28) p * M;
            M = (i28) M * m[i] / g;
            x = x % M;
        }
        if (x < L) x += (i28) ((L - x - 1) / M + 1) * M;
        return x;
    }
}

void mian() {
    s.clear();
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) std::cin >> p[i];
    for (int i = 1; i <= n; i++) std::cin >> r[i];
    for (int i = 1; i <= m; i++) std::cin >> t[i];
    for (int i = 1; i <= m; i++) s.insert(t[i]);
    for (int i = 1; i <= n; i++) {
        auto j = s.upper_bound(a[i]);
        if (j != s.begin()) j--;
        excrt::m[i] = p[i];
        excrt::a[i] = a[i];
        excrt::b[i] = *j;
        s.erase(j);
        s.insert(r[i]);
    }
    std::cout << excrt::solve() << '\n';
    return;
}

int main() {
    std::cin >> T;
    while (T--) mian();
    return 0;
}