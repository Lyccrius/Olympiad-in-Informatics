#include <iostream>
#include <cstring>
#include <algorithm>

const int maxN = 2e5;

int t;

int n;
char s[maxN + 10];
int cntA[30];
int cntB[30];
int fA;
int fB;
int ans;

void mian() {
    std::cin >> n;
    std::cin >> (s + 1);
    std::memset(cntA, 0, sizeof(cntA));
    std::memset(cntB, 0, sizeof(cntB));
    fA = 0;
    fB = 0;
    ans = 0;
    for (int i = 1; i <= n; i++) {
        int ch = s[i] - 'a' + 1;
        if (!cntB[ch]) fB++;
        cntB[ch]++;
    }
    for (int i = 1; i < n; i++) {
        char ch = s[i] - 'a' + 1;
        if (!cntA[ch]) fA++;
        cntA[ch]++;
        cntB[ch]--;
        if (!cntB[ch]) fB--;
        ans = std::max(ans, fA + fB);
    }
    std::cout << ans << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}