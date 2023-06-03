#include <iostream>
#include <set>

typedef std::multiset<int> mit;
typedef long long lxl;

int n;
int k;
int a;
mit s;
lxl ans;

void mian() {
    s.clear();
    ans = 0;
    for (int i = 1; i <= n; i++) {
        std::cin >> k;
        for (int j = 1; j <= k; j++) std::cin >> a, s.insert(a);
        int max = *s.rbegin();
        int min = *s.begin();
        ans += max - min;
        s.erase(s.find(max));
        s.erase(s.find(min));
    }
    std::cout << ans << '\n';
    return;
}

int main() {
    while (std::cin >> n && n) mian();
    return 0;
}