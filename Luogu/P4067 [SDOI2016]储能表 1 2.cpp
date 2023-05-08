#include <iostream>

typedef long long lxl;

const int maxT = 5000;
const int maxN = 100;
const int maxM = 100;
const int maxL = 100;
const int maxP = 1e9;

int T;
int n, m, k, p;
int ans;

void mian() {
    ans = 0;
    std::cin >> n >> m >> k >> p;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ans = (ans + std::max((i ^ j) - k, 0) % p) % p;
        }
    }
    std::cout << ans << '\n';
    return;
}

int main() {
    std::cin >> T;
    while (T--) mian();
    return 0;
}