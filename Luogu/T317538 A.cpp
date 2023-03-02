#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <cmath>
#include <cstring>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef std::vector<int> vic;
typedef std::deque<int> dic;
typedef double dbl;

const int maxN = 2000;
const int maxR = 5000;
const dbl pi = std::acos(- 1);

int n, r;
int x[maxN + 10], y[maxN + 10];
dbl L[maxN + 10], R[maxN + 10];
int ban[maxN + 10];
dic ans;

int q[maxN + 10];

bool cmpByL(int a, int b) {
    return L[a] < L[b];
}

bool cmpByR(int a, int b) {
    return R[a] < R[b];
}

int main() {
    std::cin >> n >> r;
    for (int i = 1; i <= n; i++) {
        std::cin >> x[i] >> y[i];
        if (x[i] * x[i] + y[i] * y[i] <= r * r) {
            ban[i] = true;
            continue;
        }
        dbl a = std::atan2(y[i], x[i]);
        dbl t = std::acos(r / std::sqrt(x[i] * x[i] + y[i] * y[i]));
        L[i] = a - t; if (a - t < - pi) L[i] += 2 * pi;
        R[i] = a + t; if (a + t > pi) R[i] -= 2 * pi;
        if (L[i] > R[i]) std::swap(L[i], R[i]);
    }
    for (int i = 1; i <= n; i++) {
        if (ban[i]) continue;
        int p[maxN + 10]; int m = 0; p[++m] = i;
        int f[maxN + 10]; std::memset(f, 0, sizeof(f));
        int g[maxN + 10]; std::memset(g, 0, sizeof(g));
        for (int j = 1; j <= n; j++) {
            if (ban[j]) continue;
            if (i == j) continue;
            if (L[i] <= L[j] &&
                R[i] <= R[j] &&
                L[j] <= R[i]) p[++m] = j;
        }
        int res = 0;
        int pos = 0;
        std::sort(p + 1, p + m + 1, cmpByL);
        for (int j = 1; j <= m; j++) {
            for (int k = 1; k < j; k++) {
                if (R[p[j]] > R[p[k]]) {
                    if (f[j] < f[k] + 1) {
                        f[j] = f[k] + 1;
                        g[j] = k;
                    }
                }
            }
        }
        for (int j = 1; j <= m; j++) {
            if (res < f[j]) {
                res = f[j];
                pos = j;
            }
        }
        if (ans.size() < res) {
            ans.clear();
            while (pos) {
                ans.push_back(p[pos]);
                pos = g[pos];
            }
        }
    }
    std::cout << ans.size() << '\n';
    for (auto i : ans) std::cout << i << ' ';
    return 0;
}