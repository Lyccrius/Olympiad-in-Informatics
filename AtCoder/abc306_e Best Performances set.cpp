#include <iostream>
#include <set>

typedef std::multiset<int> mit;
typedef long long lxl;

const int maxN = 5e5;
const int maxQ = 5e5;

int n, k, q;
int a[maxN + 10];
int x, y;
mit g, l;
lxl sum;

int main() {
    std::cin >> n >> k >> q;
    for (int i = 1; i <= n; i++) {
        if (i <= k) {
            g.insert(0);
        } else {
            l.insert(0);
        }
    }
    for (int i = 1; i <= q; i++) {
        std::cin >> x >> y;
        if (g.count(a[x])) {
            g.extract(a[x]);
            g.insert(y);
            sum += y - a[x];
        } else {
            l.extract(a[x]);
            l.insert(y);
        }
        a[x] = y;
        while (g.size() && l.size() && *g.begin() < *l.rbegin()) {
            int x = *g.begin();
            int y = *l.rbegin();
            sum += y - x;
            g.extract(x);
            l.extract(y);
            g.insert(y);
            l.insert(x);
        }
        std::cout << sum << '\n';
    }
    return 0;
}