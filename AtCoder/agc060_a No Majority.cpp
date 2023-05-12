#include <iostream>

typedef char chr;
typedef long long lxl;

const int maxN = 5000;
const int mod = 998244353;

int n;
chr s[maxN + 10];
lxl f[maxN + 10][30][30];
lxl ans;

int main() {
    std::cin >> n;
    std::cin >> (s + 1);
    if (s[1] == '?') {
        for (int a = 1; a <= 26; a++) {
            f[1][a][0] = 1;
        }
    } else {
        f[1][s[1] - 'a' + 1][0] = 1;
    }
    if (s[2] == '?') {
        for (int a = 1; a <= 26; a++) {
            for (int b = 1; b <= 26; b++) {
                if (a == b) continue;
                f[2][a][b] = (f[2][a][b] + f[1][b][0]) % mod;
            }
        }
    } else {
        for (int a = 1; a <= 26; a++) {
            if (a == s[2] - 'a' + 1) continue;
            f[2][s[2] - 'a' + 1][a] = (f[2][s[2] - 'a' + 1][a] + f[1][a][0]) % mod;
        }
    }
    for (int i = 3; i <= n; i++) {
        if (s[i] == '?') {
            for (int a = 1; a <= 26; a++) {
                for (int b = 1; b <= 26; b++) {
                    for (int c = 1; c <= 26; c++) {
                        if (a == b) continue;
                        if (a == c) continue;
                        if (b == c) continue;
                        f[i][a][b] = (f[i][a][b] + f[i - 1][b][c]) % mod;
                    }
                }
            }
        } else {
            int a = s[i] - 'a' + 1;
            for (int b = 1; b <= 26; b++) {
                for (int c = 1; c <= 26; c++) {
                    if (a == b) continue;
                    if (a == c) continue;
                    if (b == c) continue;
                    f[i][a][b] = (f[i][a][b] + f[i - 1][b][c]) % mod;
                }
            }
        }
    }
    //for (int i = 1; i <= n; i++) for (int a = 1; a <= 26; a++) for (int b = 1; b <= 26; b++) if (f[i][a][b]) printf("f[%d][%d][%d] = %d\n", i, a, b, f[i][a][b]);
    for (int a = 1; a <= 26; a++) {
        for (int b = 1; b <= 26; b++) {
            if (a == b) continue;
            ans = (ans + f[n][a][b]) % mod;
        }
    }
    std::cout << ans << '\n';
    return 0;
}