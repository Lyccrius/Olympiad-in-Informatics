#include <iostream>
#include <algorithm>
#include <cstring>

typedef char chr;

const int maxN = 1000;
const int inf = 1e9;

int t;
int n;
chr s[maxN + 10];
int p[maxN + 10][maxN + 10];
//int f[maxN + 10][maxN + 10];
int f[maxN + 10];

void mian() {
    std::cin >> (s + 1); n = std::strlen(s + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            if (i == j) {
                p[i][j] = 1;
            } else {
                p[i][j] = 0;
            }
        }
    }
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n; i++) {
            int j = (i + len - 1);
            if (j > n) break;
            if (s[i] == s[j] && (p[i + 1][j - 1] || len == 2)) p[i][j] = true;
        }
    }
    /*
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            //printf("p[%d][%d] = %d\n", i, j, p[i][j]);
        }
    }
    */
    /*
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            if (p[i][j]) {
                f[i][j] = 1;
            } else {
                f[i][j] = inf;
            }
        }
    }
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n; i++) {
            int j = (i + len - 1);
            if (j > n) break;
            for (int k = i; k < j; k++) {
                f[i][j] = std::min(f[i][j], f[i][k] + f[k + 1][j]);
            }
        }
    }
    */
    /*
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            //printf("f[%d][%d] = %d\n", i, j, f[i][j]);
        }
    }
    */
    //std::cout << f[1][n] << '\n';
    for (int i = 1; i <= n; i++) f[i] = inf;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (p[j + 1][i]) {
                f[i] = std::min(f[i], f[j] + 1);
            }
        }
    }
    std::cout << f[n] << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}