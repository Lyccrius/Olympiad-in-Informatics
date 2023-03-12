#include <iostream>
#include <algorithm>
#include <cstring>

const int maxN = 50;
const int maxT = 1e6;

int T;
int kase;
int n, t;
int a[maxN + 10];
int f[maxT + 10];
int h;

void mian() {
    std::cin >> n >> t;
    std::memset(f, 0xcf, sizeof(f)); f[0] = 1; h = 0;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) {
        for (int j = t - 1; j >= a[i]; j--) {
            f[j] = std::max(f[j], f[j - a[i]] + 1);
            if (f[j] > f[h] || (f[j] == f[h] && j > h)) {
                h = j;
            }
        }
    }
    std::cout << "Case " << kase << ": " << f[h] << " " << h + 678 << '\n';
    return;
}

int main() {
    std::cin >> T;
    for (kase = 1; kase <= T; kase++) mian();
    return 0;
}