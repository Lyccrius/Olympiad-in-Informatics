#include <iostream>
#include <algorithm>
#include <vector>

typedef bool bol;
typedef long long lxl;
typedef std::vector<lxl> vlc;

const lxl maxS = 2e9;
const lxl sqrS = 44721;

lxl s;
bol vis[sqrS + 10];
vlc prime;
lxl m;
vlc ans;

void init() {
    for (lxl i = 2; i <= sqrS; i++) {
        if (!vis[i]) prime.push_back(i);
        for (auto j : prime) {
            if (i * j > sqrS) break;
            vis[i * j] = true;
            if (i % j == 0) break;
        }
    }
    return;
}

bol isprime(lxl n) {
    if (n < sqrS) return !vis[n];
    for (lxl i = 0; prime[i] * prime[i] <= n; i++) if (n % prime[i] == 0) return false;
    return true;
}

void DFS(lxl tot, lxl now, lxl rank) {
    if (tot == 1) {
        ans.push_back(now);
        return;
    }
    if (tot > prime[rank] && isprime(tot - 1)) ans.push_back((tot - 1) * now);
    for (int i = rank; prime[i] * prime[i] <= tot; i++) {
        lxl pow = prime[i];
        lxl sum = prime[i] + 1;
        while (sum <= tot) {
            if (tot % sum == 0) DFS(tot / sum, now * pow, i + 1);
            pow *= prime[i];
            sum += pow;
        }
    }
    return;
}

void mian() {
    ans.clear();
    DFS(s, 1, 0);
    std::sort(ans.begin(), ans.end());
    std::cout << ans.size() << '\n';
    if (!ans.size()) return;
    for (auto i : ans) std::cout << i << ' ';
    std::cout << '\n';
    return;
}

int main() {
    init();
    while (scanf("%lld", &s) != EOF) mian();
    return 0;
}