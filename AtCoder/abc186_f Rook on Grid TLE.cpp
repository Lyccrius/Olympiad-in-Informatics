#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

typedef long long lxl;
typedef std::set<int> sit;
typedef std::vector<int> vic;

const int maxH = 2e5;
const int maxW = 2e5;
const int maxM = 2e5;

int h, w, m;
int x, y;
int r[maxH + 10];
int c[maxW + 10];
lxl ans;
vic t[maxW + 10];
vic s;

int main() {
    std::cin >> h >> w >> m;
    for (int i = 1; i <= h; i++) r[i] = w + 1;
    for (int i = 1; i <= w; i++) c[i] = h + 1;
    for (int i = 1; i <= m; i++) {
        std::cin >> x >> y;
        r[x] = std::min(r[x], y);
        c[y] = std::min(c[y], x);
    }
    bool flag = true;
    for (int i = 1; i <= h; i++) {
        if (flag) {
            ans += r[i] - 1;
            if (r[i] <= w) {
                t[r[i] + 1].push_back(i);
            }
            if (r[i] == 1) flag = false;
        } else {
            t[2].push_back(i);
        }
    }
    for (int i = 1; i <= w; i++) {
        if (c[i] == 1) break;
        for (auto j : t[i]) {
            //printf("insert %d\n", j);
            s.push_back(j);
        }
        if (t[i].size()) {
            std::sort(s.begin(), s.end());
        }
        /*
        while (s.size() && *s.rbegin() >= c[i]) {
            //printf("erase %d\n", *s.rbegin());
            s.erase(*s.rbegin());
        }
        */
        //ans += s.size();
        ans += std::lower_bound(s.begin(), s.end(), c[i]) - s.begin();
        //printf("%d: %d\n", i, s.size());
    }
    std::cout << ans << '\n';
    return 0;
}