#include <iostream>
#include <set>

typedef std::multiset<int> mit;

const int maxN = 10000;
const int maxK = 26;

int t;
int n, k;
int a[maxK + 10];
int tot;
int res;
int ans;
mit s;

void mian() {
    tot = 0;
    res = 0;
    ans = 2147483647;
    s.clear();
    std::cin >> n >> k;
    for (int i = 1; i <= k; i++) std::cin >> a[i];
    for (int i = 1; i <= k; i++) s.insert(a[i]);
    for (int i = 1; i <= k; i++) tot += a[i];
    res = tot;
    while (true) {
        if (res >= ans) break;
        if (s.size() == n) ans = res;
        auto it = s.begin();
        res += tot + k * (*it);
        for (int i = 1; i <= k; i++) s.insert(a[i] + *it);
        res -= *it;
        s.erase(it);
        while (s.size() > n) {
            auto it = s.end();
            it--;
            res -= *it;
            s.erase(it);
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