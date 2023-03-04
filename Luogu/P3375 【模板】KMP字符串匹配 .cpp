#include <iostream>
#include <vector>
#include <cstring>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1e6;
const int maxM = 1e6;

char s1[maxN + 10];
char s2[maxM + 10];

int n;
int m;

int next[maxN + 10];
int f[maxM + 10];
std::vector<int> appear;

void KMP() {
    next[1] = 0;
    for (int i = 2, j = 0; i <= m; i++) {
        while (j > 0 && s2[i] != s2[j + 1]) j = next[j];
        if (s2[i] == s2[j + 1]) j++;
        next[i] = j;
    }
    for (int i = 1, j = 0; i <= n; i++) {
        while (j > 0 && s1[i] != s2[j + 1]) j = next[j];
        if (s1[i] == s2[j + 1]) j++;
        f[i] = j;
        if (f[i] == m) appear.push_back(i - m + 1);
    }
    return;
}

int main() {
    promote();
    std::cin >> (s1 + 1); n = std::strlen(s1 + 1);
    std::cin >> (s2 + 1); m = std::strlen(s2 + 1);
    KMP();
    for (auto pos : appear) std::cout << pos << '\n';
    for (int i = 1; i <= m; i++) std::cout << next[i] << ' ';
    return 0;
}