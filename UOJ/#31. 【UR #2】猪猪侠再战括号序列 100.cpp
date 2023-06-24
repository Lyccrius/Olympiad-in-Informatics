#include <iostream>
#include <vector>
#include <cstring>

typedef char chr;
typedef std::pair<int, int> pii;
typedef std::vector<pii> vpc;

const int maxN = 100000;

int n;
chr a[2 * maxN + 10];
vpc ans;

int main() {
    std::cin >> (a + 1);
    n = strlen(a + 1) / 2;
    int l = 1;
    int r = 0;
    while (l <= n) {
        if (a[l] == ')') {
            r = std::max(r, l + 1);
            while (a[r] == ')') r++;
            ans.push_back(std::make_pair(l, r));
            std::swap(a[l], a[r]);
        }
        l++;
    }
    if (ans.size() <= n) {
        std::cout << ans.size() << '\n';
        for (auto i : ans) std::cout << i.first << ' ' << i.second << '\n';
    } else {
        std::cout << -1 << '\n';
    }
    return 0;
}