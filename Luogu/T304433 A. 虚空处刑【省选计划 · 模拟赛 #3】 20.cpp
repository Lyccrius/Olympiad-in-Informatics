#include <iostream>

const int maxN = 5e5;
const int maxM = 5e5;

int n, m;
int a[maxN + 10];
int opt[maxM + 10], l[maxM + 10], r[maxM + 10], x[maxM + 10];

namespace S1 {
    bool is() {
        return (n <= 1000) && (m <= 1000);
    }

    int f(int l, int r) {
        int ret = 0;
        for (int i = l; i < r; i++) {
            if (a[i] != a[i + 1]) {
                ret++;
            }
        }
        return ret;
    }

    void mian() {
        for (int i = 1; i <= m; i++) {
            if (opt[i] == 1) {
                for (int j = l[i]; j <= r[i]; j++) a[j] = x[i];
            } else if (opt[i] == 2) {
                int ans = 0;
                for (int j = l[i]; j <= r[i]; j++) {
                    for (int k = j + 1; k <= r[i]; k++) {
                        if ((a[j] == x[i]) && (a[k] == x[i])) {
                            ans += f(j, k);
                        }
                    }
                }
                std::cout << ans << '\n';
            }
        }
        return;
    }
}

namespace S2 {
    bool is() {
        for (int i = 1; i <= m; i++) if (opt[i] == 1) return false;
        return true;
    }

    int f[maxN + 10];

    void mian() {

    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= m; i++) std::cin >> opt[i] >> l[i] >> r[i] >> x[i];
    if (S1::is()) S1::mian();
    else if (S2::is()) S2::mian();
    return 0;
}