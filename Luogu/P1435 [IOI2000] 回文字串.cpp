#include <iostream>
#include <algorithm>
#include <string>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1000;

std::string s1;
std::string s2;
int n;
int f[2][maxN + 10];
int cur;

int main() {
    std::cin >> s1;
    s2 = s1;
    std::reverse(s2.begin(), s2.end());
    for (int i = 1; i <= s1.size(); i++, cur ^= 1) {
        for (int j = 1; j <= s2.size(); j++) {
            f[cur][j] = std::max(f[cur][j - 1], f[cur ^ 1][j]);
            if (s1[i - 1] == s2[j - 1]) {
                f[cur][j] = std::max(f[cur][j], f[cur ^ 1][j - 1] + 1);
            }
        }
    }
    std::cout << s1.size() - f[cur ^ 1][s2.size()] << '\n';
    return 0;
}//