#include <iostream>
#include <set>

typedef std::set<int> sit;

const int maxN = 1e5;
const int sqrN = 317;

int n;
int a[maxN + 10];
int ans[maxN + 10];

int solve(int k) {
    sit s;
    int ret = 1;
    for (int i = 1; i <= n; i++) {
        s.insert(a[i]);
        if (s.size() > k) {
            s.clear();
            s.insert(a[i]);
            ret++;
        }
    }
    return ret;
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int k = 1; k <= std::min(sqrN, n); k++) ans[k] = solve(k);
    for (int k = sqrN + 1; k <= n; k++) {
        ans[k] = solve(k);
        int l = k;
        int r = n;
        while (l < r) {
            int mid = (l + r + 1) / 2;
            if (solve(mid) == ans[k]) l = mid;
            else r = mid - 1;
        }
        for (int j = k; j <= r; j++) ans[j] = ans[k];
        k = r;
    }
    for (int k = 1; k <= n; k++) std::cout << ans[k] << ' ';
    std::cout << '\n';
    return 0;
}