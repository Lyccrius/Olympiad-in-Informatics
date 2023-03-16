#include <iostream>

const int maxN = 100;
const int maxM = 100;
const int maxK = 10;
const int inf = 1e9 + 10;

int n, m, p;
int a[maxN + 10][maxM + 10];
int f[maxN + 10][maxM + 10][maxK + 10];
int g[maxN + 10][maxM + 10][maxK + 10];

int mod(int x) {
    return (x % p + p) % p;
}

void print(int i, int j, int k) {
    if (i == n) {
        std::cout << j << '\n';
        return;
    }
    if (g[i][j][k] == 0) {
        print(i + 1, j + 1, mod(k - a[i][j]));
        std::cout << 'L';
    } else {
        print(i + 1, j - 1, mod(k - a[i][j]));
        std::cout << 'R';
    }
    return;
}

int main() {
    std::cin >> n >> m >> p; p++;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf("%1d", &a[i][j]);
    std::fill(f[0][0], f[0][0] + (maxN + 10) * (maxM + 10) * (maxK + 10), - 1);
    for (int j = 1; j <= m; j++) f[n][j][mod(a[n][j])] = a[n][j];
    for (int i = n - 1; i >= 1; i--) {
        for (int j = 1; j <= m; j++) {
            for (int k = 0; k < p; k++) {
				int l = f[i + 1][j + 1][mod(k - a[i][j])];
                int r = f[i + 1][j - 1][mod(k - a[i][j])];
				if (j < m && ~ l && f[i][j][k] < l + a[i][j]) {
					f[i][j][k] = l + a[i][j];
					g[i][j][k] = 0;
				}
				if (j > 1 && ~ r && f[i][j][k] < r + a[i][j]) {
					f[i][j][k] = r + a[i][j];
					g[i][j][k] = 1;
				}
            }
        }
    }
    int pos = 0;
    for (int j = 1; j <= m; j++) if (f[1][j][0] > f[1][pos][0]) pos = j;
    if (f[1][pos][0] == - 1) {
        std::cout << - 1;
        return 0;
    }
    std::cout << f[1][pos][0] << '\n';
    print(1, pos, 0);
    return 0;
}