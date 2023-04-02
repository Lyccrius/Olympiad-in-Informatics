#include <iostream>
#include <deque>

typedef std::deque<int> diq;

const int maxN = 2e5;
const int maxM = 2e5;

int n, m, x;
int l[maxM + 10], r[maxM + 10];
int s[maxN + 10], t[maxN + 10];
int a[maxN + 10];
diq ans;

int main() {
    freopen("station.in", "r", stdin);
    freopen("station.out", "w", stdout);
    std::cin >> n >> m >> x;
    for (int i = 1; i <= m; i++) {
        std::cin >> l[i] >> r[i];
        s[l[i]] = true;
        t[r[i]] = true;
        a[l[i]]++;
        a[r[i] + 1]--;
    }
    for (int i = 1; i <= n; i++) a[i] += a[i - 1];
    for (int i = x; i >= 1 && a[i]; i--) {
        if (s[i] && i != x) {
            ans.push_front(i);
        }
    }
    for (int i = x; i <= n && a[i]; i++) {
        if (t[i] && i != x) {
            ans.push_back(i);
        }
    }
    for (auto i : ans) std::cout << i << ' ';
    std::cout << '\n';
    return 0;
}