#include <iostream>
#include <cstring>
#include <algorithm>

typedef char chr;

const int maxN = 50;

int t;
int n;
chr s[maxN + 10];
int a[maxN + 10][maxN + 10];

void mian() {
    std::memset(a, 0, sizeof(a));
    std::cin >> (s + 1);
    n = strlen(s + 1);
    int ans = -1;
    for (int i = 1; i <= n; i++) a[i][i] = true;
    for (int i = 1; i <= n; i++) a[i][i - 1] = true;
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n; i++) {
            int j = i + len - 1;
            if (j > n) break;
            if (s[i] == s[j]) {
                a[i][j] = a[i + 1][j - 1];
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            if (a[i][j] == 0) {
                ans = std::max(ans, j - i + 1);
            }
        }
    }
    std::cout << ans << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}