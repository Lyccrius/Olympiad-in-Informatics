#include <iostream>
#include <cstring>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 100;
const int sco[5][5] = {
    {0, -3, -4, -2, -1},
    {-3, 5, -1, -2, -1},
    {-4, -1, 5, -3, -2},
    {-2, -2, -3, 5, -2},
    {-1, -1, -2, -2, 5},
};

int n, m;
char ch;
int a[maxN + 10];
int b[maxN + 10];
int f[maxN + 10][maxN + 10];

void transform(char ch, int &x) {
    if (ch == 'A') x = 1;
    if (ch == 'C') x = 2;
    if (ch == 'G') x = 3;
    if (ch == 'T') x = 4;
    return;
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> ch;
        transform(ch, a[i]);
    }
    std::cin >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> ch;
        transform(ch, b[i]);
    }
    for (int i = 1; i <= n; i++) f[i][0] = f[i - 1][0] + sco[a[i]][0];
    for (int j = 1; j <= m; j++) f[0][j] = f[0][j - 1] + sco[0][b[j]];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            f[i][j] = std::max(f[i - 1][j] + sco[a[i]][0], f[i][j - 1] + sco[0][b[j]]);
            f[i][j] = std::max(f[i][j], f[i - 1][j - 1] + sco[a[i]][b[j]]);
        }
    }
    std::cout << f[n][m] << '\n';
    return 0;
}