#include <iostream>
#include <cstring>
#include <algorithm>

typedef char chr;

const int maxT = 2e4;
const int maxN = 2e5;

int t;
int n;
chr s[maxN + 10];
int a[maxN + 10];
int b[maxN + 10];
int pre;
int suf;

void mian() {
    std::cin >> (s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; i++) a[i] = s[i] - '0';
    for (int i = 1; i <= n; i++) {
        if (a[i]) {
            b[i] = b[i - 1] + 1;
        } else {
            b[i] = 0;
        }
    }
    pre = 0;
    suf = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] == 0) break;
        pre++;
    }
    for (int i = n; i >= 1; i--) {
        if (a[i] == 0) break;
        suf++;
    }
    int tot = 0;
    for (int i = 1; i <= n; i++) tot = std::max(tot, b[i]);
    if (pre != n) tot = std::max(tot, pre + suf);
    long long ans = 1;
    if (tot == n) {
        ans = 1ll * n * n;
    } else {
        ans = 1ll * ((tot + 1) / 2) * (tot + 1 - (tot + 1) / 2);
    }
    //ans = std::max(ans, 1ll);
    std::cout << ans << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}