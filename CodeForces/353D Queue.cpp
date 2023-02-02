#include <iostream>
#include <cstring>

typedef long long lxl;

const int maxN = 1e6;

char s[maxN + 10];
int n;
lxl cnt;
lxl ans = 0;

int main() {
    std::cin >> (s + 1);
    n = std::strlen(s + 1);
    for (int i = 1; i <= n; i++) {
        if (s[i] == 'M') cnt++;
        else if (cnt) ans = std::max(ans + 1, cnt);
    }
    std::cout << ans;
    return 0;
}