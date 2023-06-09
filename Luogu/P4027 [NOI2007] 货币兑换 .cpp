#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>

typedef double dbl;
typedef std::vector<dbl> vdc;

const int maxN = 1e5;

int n, s;
dbl a[maxN + 10], b[maxN + 10], r[maxN + 10];
dbl k[maxN + 10], c[maxN + 10];
dbl f[maxN + 10];
vdc raw;

dbl calc(int adv, int pos) {
    return k[adv] * raw[pos] + c[adv];
}

struct SegmentTree {
    struct Node {
        int adv;
    } node[4 * maxN + 10];

    void update(int u, int l, int r, int adv) {
        if (l == r) {
            if (calc(node[u].adv, l) < calc(adv, l)) node[u].adv = adv;
            return;
        }
        int mid = (l + r) / 2;
        if (calc(node[u].adv, mid) < calc(adv, mid)) std::swap(node[u].adv, adv);
        if (calc(node[u].adv, l) < calc(adv, l)) update(2 * u, l, mid, adv);
        if (calc(node[u].adv, r) < calc(adv, r)) update(2 * u + 1, mid + 1, r, adv);
        return;
    }

    dbl query(int u, int l, int r, int pos) {
        if (l == r) return calc(node[u].adv, pos);
        int mid = (l + r) / 2;
        dbl ret = calc(node[u].adv, pos);
        if (pos <= mid) ret = std::max(ret, query(2 * u, l, mid, pos));
        if (pos >= mid + 1) ret = std::max(ret, query(2 * u + 1, mid + 1, r, pos));
        return ret;
    }
} sgt;

int main() {
    std::cin >> n >> s;
    f[0] = s;
    for (int i = 1; i <= n; i++) std::cin >> a[i] >> b[i] >> r[i];
    for (int i = 1; i <= n; i++) raw.push_back(a[i] / b[i]);
    std::sort(raw.begin(), raw.end());
    raw.erase(std::unique(raw.begin(), raw.end()), raw.end());
    for (int i = 1; i <= n; i++) {
        int pos = std::lower_bound(raw.begin(), raw.end(), a[i] / b[i]) - raw.begin();
        f[i] = std::max(f[i - 1], b[i] * sgt.query(1, 0, raw.size() - 1, pos));
        k[i] = f[i] * r[i] / (a[i] * r[i] + b[i]);
        c[i] = f[i] / (a[i] * r[i] + b[i]);
        sgt.update(1, 0, raw.size() - 1, i);
    }
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(3) << f[n] << '\n';
    return 0;
}