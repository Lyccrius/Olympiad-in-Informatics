#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const int maxN = 19;

int n, m;
int a, b;
int e[maxN + 10][maxN + 10];
lxl f[(1 << maxN) + 10][maxN + 10];
lxl ans;

int lowbit(int x) {
    return x & -x;
}

int main() {
    promote();
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> a >> b;
        e[a][b] = true;
        e[b][a] = true;
    }
    for (int s = 1, i = 1; i <= n; s <<= 1, i++) f[s][i] = 1;
    for (int s = 1; s <= (1 << n); s++) {
        for (int i = 1; i <= n; i++) {
            if (!((1 << (i - 1)) & s) || !f[s][i]) continue;
            for (int j = 1; j <= n; j++) {
                if (lowbit(s) > (1 << (j - 1)) || !e[i][j]) continue;
                if (lowbit(s) == (1 << (j - 1))) ans += f[s][i];
                else if (!((1 << (j - 1)) & s)) f[s ^ (1 << (j - 1))][j] += f[s][i];
            }
        }
    }
    std::cout << ((ans - m) >> 1) << '\n';
    return 0;
}