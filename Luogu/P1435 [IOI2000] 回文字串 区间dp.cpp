#include <iostream>
#include <string>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1000;

std::string s;
int n;
int f[maxN + 10][maxN + 10];

int main() {
    std::cin >> s;
    n = s.size();
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n; i++) {
            int j = i + len - 1;
            f[i][j] = std::min(f[i][j - 1], f[i + 1][j]) + 1;
            if (s[i - 1] == s[j - 1]) f[i][j] = std::min(f[i][j], f[i + 1][j - 1]);
        }
    }
    std::cout << f[1][n] << '\n';
    return 0;
}