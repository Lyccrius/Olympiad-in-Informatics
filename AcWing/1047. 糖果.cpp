#include <iostream>
#include <algorithm>

const int maxN = 100;
const int maxK = 100;
const int inf = 1e9 + 10;

int n, k;
int a[maxN + 10];
int f[maxN + 10][maxK + 10];

int main() {
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 0; i <= n; i++) for (int j = 1; j < k; j++) f[i][j] = - inf;
    for (int i = 1; i <= n; i++) for (int j = k - 1; j >= 0; j--) f[i][j] = std::max(f[i - 1][j], f[i - 1][((j - a[i]) % k + k) % k] + a[i]);
    std::cout << f[n][0];
    return 0;
}