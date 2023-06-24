#include <iostream>
#include <vector>
#include <cstring>

typedef char chr;
typedef std::pair<int, int> pii;
typedef std::vector<pii> vpc;

const int maxN = 100;

int n;
chr a[2 * maxN + 10];
vpc ans;

int main() {
    std::cin >> (a + 1);
    n = strlen(a + 1) / 2;
    for (int i = 1; i <= n; i++) {
        if (a[i] == ')') {
            for (int j = 2 * n; j >= i + 1; j--) {
                if (a[j] == '(') {
                    ans.push_back(std::make_pair(i, j));
                    for (int k = 0; i + k <= j - k; k++) std::swap(a[i + k], a[j - k]);
                    break;
                }
            }
        }
    }
    if (ans.size() <= n) {
        std::cout << ans.size() << '\n';
        for (auto i : ans) std::cout << i.first << ' ' << i.second << '\n';
    } else {
        std::cout << -1 << '\n';
    }
    return 0;
}