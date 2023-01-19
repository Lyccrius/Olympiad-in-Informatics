#include <iostream>
#include <map>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const int maxN = 1e5;

int t;
int n;
int a[maxN + 10];
int p[maxN + 10];
std::map<lxl, lxl> mp;

void mian() {
    long long ans = 0;
    mp.clear();
    mp[0] = 1;
    std::cin >> n;
    for (int i = 1; i <= n; i++) scanf("%1d", &a[i]);
    for (int i = 1; i <= n; i++) p[i] = p[i - 1] + a[i];
    for (int i = 1; i <= n; i++) ans += mp[p[i] - i], mp[p[i] - i]++;
    std::cout << ans << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}