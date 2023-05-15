#include <iostream>
#include <vector>

typedef std::vector<int> vic;

const int maxN = 1e5;
const int maxM = 1e5;
const int maxA = 1e5;

int n, m;
int a;
vic b[maxA + 1];
int opt, x, y;
int ans;
int res;

vic merge(vic a, vic b) {
    vic ret;
    int i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] <= b[j]) {
            ret.push_back(a[i]);
            i++;
        } else {
            ret.push_back(b[j]);
            j++;
        }
    }
    while (i < a.size()) {
        ret.push_back(a[i]);
        i++;
    }
    while (j < b.size()) {
        ret.push_back(b[j]);
        j++;
    }
    return ret;
}

int query(vic a, vic b) {
    if (a.empty()) return -1;
    if (b.empty()) return -1;
    int i = 0, j = 0;
    int ret = maxN;
    while (i < a.size() && j < b.size()) {
        ret = std::min(ret, std::abs(a[i] - b[j]));
        if (a[i] <= b[j]) {
            i++;
        } else {
            j++;
        }
    }
    return ret;
}

void clear(vic &a) {
    vic e;
    a.swap(e);
    return;
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a, b[a].push_back(i);
    for (int i = 1; i <= m; i++) {
        std::cin >> opt >> x >> y;
        x ^= ans;
        y ^= ans;
        if (opt == 1) {
            if (x == y) continue;
            b[y] = merge(b[x], b[y]);
            clear(b[x]);
        } else if (opt == 2) {
            res = query(b[x], b[y]);
            if (~res) {
                std::cout << res << '\n';
                ans = res;
            } else {
                std::cout << "Ikaros" << '\n';
                ans = 0;
            }
        }
    }
    return 0;
}