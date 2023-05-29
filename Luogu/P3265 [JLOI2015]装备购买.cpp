#include <iostream>
#include <algorithm>

typedef double dbl;

const int maxN = 500;
const int maxM = 500;
const int maxA = 1000;
const dbl eps = 1e-5;

int n, m;
int cnt;
int ans;

struct Equipment {
    dbl a[maxM + 10];
    dbl c;

    bool operator<(const Equipment &other) const {
        return c < other.c;
    }
} z[maxN + 10];

int b[maxM + 10];

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) std::cin >> z[i].a[j];
    for (int i = 1; i <= n; i++) std::cin >> z[i].c;
    std::sort(z + 1, z + n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (std::abs(z[i].a[j]) < eps) continue;
            if (!b[j]) {
                b[j] = i;
                cnt++;
                ans += z[i].c + 0.5;
                break;
            } else {
                for (int k = m; k >= j; k--) z[i].a[k] -= z[i].a[j] / z[b[j]].a[j] * z[b[j]].a[k];
            }
        }
    }
    std::cout << cnt << ' ' << ans << '\n';
    return 0;
}