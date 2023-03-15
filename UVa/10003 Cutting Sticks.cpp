#include <iostream>

const int maxL = 1000;
const int maxN = 50;
const int inf = 1e9;

int l;
int n;
int c[maxN + 10];
int f[maxN + 10][maxN + 10];

void mian() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> c[i]; c[n + 1] = l;
    for (int i = 0; i <= n + 1; i++) for (int j = 0; j <= n + 1; j++) f[i][j] = inf;
    for (int i = 1; i <= n + 1; i++) f[i - 1][i] = 0;
    for (int len = 3; len <= n + 2; len++) {
        for (int i = 0; i <= n + 1; i++) {
            int j = i + len - 1;
            if (j > n + 1) break;
            for (int k = i + 1; k < j; k++) {
                f[i][j] = std::min(f[i][j], f[i][k] + f[k][j] + c[j] - c[i]);
            }
        }
    }
    //for (int i = 0; i <= n + 1; i++) for (int j = i + 1; j <= n + 1; j++) printf("f[%d][%d] = %d\n", i, j, f[i][j]);
    //std::cout << f[0][n + 1] << '\n';
    std::cout << "The minimum cutting is " << f[0][n + 1] << "." << '\n';
    return;
}

int main() {
    while (std::cin >> l && l) mian();
    return 0;
}