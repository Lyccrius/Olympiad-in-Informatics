#include <iostream>
#include <algorithm>

const int maxN = 1000;
const int maxX = 5000;

int n, x;
int a[maxN + 10];
int f[maxN + 10][maxX + 10];

int main() {
    std::cin >> n >> x;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    std::sort(a + 1, a + n + 1);
    std::reverse(a + 1, a + n + 1);
    f[0][x] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= x; j++) f[i][j] |= f[i - 1][j];
        for (int j = 0; j <= x; j++) f[i][j % a[i]] |= f[i - 1][j];
    }
    for (int y = a[n] - 1; y >= 0; y--) {
        if (f[n][y]) {
            std::cout << y << '\n';
            std::cout << f[n][y] << '\n';
            break;
        }
    }
    return 0;
}