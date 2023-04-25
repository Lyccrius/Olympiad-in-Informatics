#include <iostream>
#include <cstring>

typedef char chr;

const int maxT = 100;
const int maxN = 100;

int t;
chr s[maxN + 10];
int a[maxN + 10];
int n;

void mian() {
    std::cin >> (s + 1);
    n = strlen(s + 1);
    for (int i = 0; i <= n + 1; i++) a[i] = 0;
    int ans = 0;
    if (n == 1 && s[1] == '^') {
        std::cout << 1 << '\n';
        return;
    }
    for (int i = 1; i < n; i++) {
        if (s[i] == '^' && s[i + 1] == '^') continue;
        if (s[i] == '_' && s[i + 1] == '_') ans++;
    }
    if (s[1] == '_') ans++;
    if (s[n] == '_') ans++;
    std::cout << ans << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}