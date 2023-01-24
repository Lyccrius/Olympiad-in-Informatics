#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxS = 40;
const int maxN = 1e5;
const int inf = 1e9;

std::string s;
int n;
int t[maxS + 10][maxS + 10];
int f[maxS + 10][maxN + 10];

int main() {
    promote();
    std::cin >> s >> n;
    std::memset(f, 0x3f, sizeof(f));
    f[0][0] = -1;
    for (int i = 1; i <= s.size(); i++) {
        for (int j = 1; j <= i; j++) {
            t[j][i] = t[j][i - 1] * 10 + s[i - 1] - '0';
        }
    }
    for (int i = 1; i <= s.size(); i++) {
        for (int k = 0; k <= n; k++) {
            for (int j = i - 1; j >= 0; j--) {
                if (k >= t[j + 1][i]) {
                    f[i][k] = std::min(f[i][k], f[j][k - t[j + 1][i]] + 1);
                }
            }
        }
    }
    if (f[s.size()][n] == 0x3f3f3f3f) f[s.size()][n] = -1;
    std::cout << f[s.size()][n];
    return 0;
}