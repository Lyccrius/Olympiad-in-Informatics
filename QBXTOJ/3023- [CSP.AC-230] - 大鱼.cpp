#include <iostream>
#include <algorithm>

typedef long long lxl;

const lxl maxN = 1e18;

lxl n;
lxl ans = maxN;

int main() {
    std::cin >> n;
    for (lxl i = 0; i <= 4; i++) {
        for (lxl j = 0; j <= 1; j++) {
            for (lxl k = 0; k <= 1; k++) {
                for (lxl l = 0; l <= 4; l++) {
                    for (lxl q = 0; q <= 1; q++) {
                        lxl tot = 0;
                        tot += 2 * i;
                        tot += 5 * j;
                        tot += 10 * k;
                        tot += 20 * l;
                        tot += 50 * q;
                        lxl remain = n - tot;
                        lxl r = remain / 100;
                        if (remain < 0) continue;
                        tot += 100 * r;
                        if (tot == n) ans = std::min(ans, i + j + k + l + q + r);
                    }
                }
            }
        }
    }
    std::cout << ans;
    return 0;
}