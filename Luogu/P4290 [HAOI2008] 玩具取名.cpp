#include <iostream>
#include <cstring>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 200;

int c[5];
char ch1, ch2;
char str[maxN + 10];
int n;
int f[maxN + 10][maxN + 10][5];
int g[5][5][5];

int trans(char ch) {
    if (ch == 'W') return 1;
    if (ch == 'I') return 2;
    if (ch == 'N') return 3;
    if (ch == 'G') return 4;
}

char snart(int x) {
    if (x == 1) return 'W';
    if (x == 2) return 'I';
    if (x == 3) return 'N';
    if (x == 4) return 'G';
}

int main() {
    for (int i = 1; i <= 4; i++) std::cin >> c[i];
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= c[i]; j++) {
            std::cin >> ch1 >> ch2;
            g[i][trans(ch1)][trans(ch2)] = true;
        }
    }
    std::cin >> str;
    n = std::strlen(str);
    for (int i = 1; i <= n; i++) f[i][i][trans(str[i - 1])] = true;
    for (int len = 1; len <= n; len++) {
        for (int i = 1; i <= n; i++) {
            int j = i + len - 1;
            if (j > n) break;
            for (int k = i; k < j; k++) {
                for (int c = 1; c <= 4; c++) {
                    for (int c1 = 1; c1 <= 4; c1++) {
                        for (int c2 = 1; c2 <= 4; c2++) {
                            if (g[c][c1][c2] && f[i][k][c1] && f[k + 1][j][c2]) {
                                f[i][j][c] = true;
                            }
                        }
                    }
                }
            }
        }
    }
    bool ok = false;
    for (int i = 1; i <= 4; i++) {
        if (f[1][n][i]) {
            ok = true;
            std::cout << snart(i);
        }
    }
    if (!ok) std::cout << "The name is wrong!";
    return 0;
}