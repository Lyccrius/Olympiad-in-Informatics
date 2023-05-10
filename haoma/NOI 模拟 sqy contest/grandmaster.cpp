#include <iostream>
#include <algorithm>

typedef double dbl;

const int maxN = 1e5;
const int maxV = 1e6;
const int maxM = 1e6;

int T;
int n;
int V[maxN + 10];
int m[maxN + 10];

namespace S1 {
    bool is() {
        return n <= 3;
    }

    namespace ans {
        int k;
        int a[maxN + 10];
        int b[maxN + 10];
        dbl p[maxN + 10];
        dbl eps;
    }

    namespace res {
        int k;
        int a[maxN + 10];
        int b[maxN + 10];
        int v[maxN + 10];
        int m[maxN + 10];
        dbl p[maxN + 10];
        dbl eps;
    }

    void calc(int sv, int tv, int sm, int tm) {
        res::eps = std::abs(1.0 * (sv - tv) / (sv + tv)) + std::abs(1.0 * (sm - tm) / (sm + tm));
    }

    void update() {
        ans::k = res::k;
        for (int i = 1; i <= n + res::k; i++) {
            ans::a[i] = res::a[i];
            ans::b[i] = res::b[i];
            ans::p[i] = res::p[i];
        }
        ans::eps = res::eps;
        return;
    }

    void DFS(int now, int sv, int tv, int sm, int tm) {
        //printf("DFS(%d, %d, %d, %d, %d)\n", now, sv, tv, sm, tm);
        if (now > n + res::k) {
            calc(sv, tv, sm, tm);
            if (ans::eps > res::eps) {
                update();
            }
            return;
        }
        res::a[now] = 0;
        DFS(now + 1, sv + res::v[now], tv, sm + res::m[now], tm);
        res::a[now] = 1;
        DFS(now + 1, sv, tv + res::v[now], sm, tm + res::m[now]);
        return;
    }

    void solve0() {
        res::k = 0;
        for (int i = 1; i <= n; i++) res::b[i] = 0;
        for (int i = 1; i <= n; i++) res::v[i] = V[i];
        for (int i = 1; i <= n; i++) res::m[i] = m[i];
        DFS(1, 0, 0, 0, 0);
        return;
    }

    void solve1() {
        res::k = 1;
        for (int i = 1; i <= n; i++) res::b[i] = 0;
        for (int i = 1; i <= n; i++) res::v[i] = V[i];
        for (int i = 1; i <= n; i++) res::m[i] = m[i];
        for (int i = 1; i <= n; i++) {
            res::b[i] = 1;
            for (int ii = 1; ii <= V[i]; ii++) {
                if (V[i] % ii) continue;
                if (m[i] % ii) continue;
                res::p[i] = 1.0 * ii / V[i];
                res::v[i] = res::p[i] * V[i];
                res::m[i] = res::p[i] * m[i];
                res::v[n + 1] = (1.0 - res::p[i]) * V[i];
                res::m[n + 1] = (1.0 - res::p[i]) * m[i];
                DFS(1, 0, 0, 0, 0);
                res::v[i] = V[i];
                res::m[i] = m[i];
            }
            res::b[i] = 0;
        }
        return;
    }

    void solve2() {
        res::k = 2;
        for (int i = 1; i <= n; i++) res::b[i] = 0;
        for (int i = 1; i <= n; i++) res::v[i] = V[i];
        for (int i = 1; i <= n; i++) res::m[i] = m[i];
        for (int i = 1; i <= n; i++) {
            res::b[i] = 1;
            for (int j = i + 1; j <= n; j++) {
                res::b[j] = 1;
                for (int ii = 1; ii <= V[i]; ii++) {
                    if (V[i] % ii) continue;
                    if (m[i] % ii) continue;
                    res::p[i] = 1.0 * ii / V[i];
                    res::v[i] = res::p[i] * V[i];
                    res::m[i] = res::p[i] * m[i];
                    res::v[n + 1] = (1.0 - res::p[i]) * V[i];
                    res::m[n + 1] = (1.0 - res::p[i]) * m[i];
                    for (int jj = 1; jj <= V[j]; jj++) {
                        if (V[j] % jj) continue;
                        if (m[j] % jj) continue;
                        res::p[j] = 1.0 * jj / V[j];
                        res::v[j] = res::p[j] * V[j];
                        res::m[j] = res::p[j] * m[j];
                        res::v[n + 2] = (1.0 - res::p[j]) * V[j];
                        res::m[n + 2] = (1.0 - res::p[j]) * m[j];
                        DFS(1, 0, 0, 0, 0);
                        res::v[j] = V[j];
                        res::m[j] = m[j];
                    }
                    res::v[i] = V[i];
                    res::m[i] = m[i];
                }
                res::b[j] = 0;
            }
            res::b[i] = 0;
        }
    }

    void mian() {
        ans::eps = 2;
        solve0();
        solve1();
        solve2();
        std::cout << ans::k << '\n';
        for (int i = 1; i <= n; i++) {
            if (ans::b[i]) {
                std::cout << i << ' ' << ans::p[i] << '\n';
            }
        }
        for (int i = 1; i <= n + ans::k; i++) std::cout << ans::a[i] << ' ';
        std::cout << '\n';
        return;
    }
}

namespace SA {
    bool is() {
        return n <= 30;
    }

    namespace ans {
        int a[maxN + 10];
        dbl eps;
    }

    namespace res {
        int a[maxN + 10];
        dbl eps;
    }

    void calc(int sv, int tv, int sm, int tm) {
        res::eps = std::abs(1.0 * (sv - tv) / (sv + tv)) + std::abs(1.0 * (sm - tm) / (sm + tm));
    }

    void update() {
        for (int i = 1; i <= n; i++) {
            ans::a[i] = res::a[i];
        }
        ans::eps = res::eps;
        return;
    }

    void DFS(int now, int sv, int tv, int sm, int tm) {
        //printf("DFS(%d, %d, %d, %d, %d)\n", now, sv, tv, sm, tm);
        if (now > n) {
            calc(sv, tv, sm, tm);
            if (ans::eps > res::eps) {
                update();
            }
            return;
        }
        res::a[now] = 0;
        DFS(now + 1, sv + V[now], tv, sm + m[now], tm);
        res::a[now] = 1;
        DFS(now + 1, sv, tv + V[now], sm, tm + m[now]);
        return;
    }

    void mian() {
        ans::eps = 2;
        DFS(1, 0, 0, 0, 0);
        std::cout << 0 << '\n';
        for (int i = 1; i <= n; i++) std::cout << ans::a[i] << ' ';
        std::cout << '\n';
        return;
    }
}

void mian() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> V[i];
    for (int i = 1; i <= n; i++) std::cin >> m[i];
    if (S1::is()) S1::mian();
    else if (SA::is()) SA::mian();
    return;
}

int main() {
    freopen("grandmaster.in", "r", stdin);
    freopen("grandmaster.out", "w", stdout);
    std::cin >> T;
    while (T--) mian();
    return 0;
}