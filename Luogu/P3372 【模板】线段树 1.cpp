#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const int maxN = 1e5;
const int maxM = 1e5;

int n, m;
lxl a[maxN + 10];
lxl o, x, y, k;

struct ZKWSegmentTree {
    struct Node {
        lxl val;
        lxl tag;
    } node[maxN * 4 + 10];

    int N;

    void Build() {
        N = 1;
        while (N <= n + 1) N *= 2;
        for (int i = N + 1; i <= N + n; i++) node[i].val = a[i - N];
        for (int i = N - 1; i >= 1; i--) node[i].val = node[i * 2].val + node[i * 2 + 1].val;
        return;
    }

    void Add(int s, int t, lxl val) {
        int l = N + s - 1;
        int r = N + t + 1;
        lxl lcnt = 0;
        lxl rcnt = 0;
        lxl ncnt = 1;
        while (l / 2 != r / 2) {
            node[l].val += lcnt * val;
            node[r].val += rcnt * val;
            if ((l & 1) == 0) {
                node[l + 1].tag += val;
                node[l + 1].val += ncnt * val;
                lcnt += ncnt;
            }
            if ((r & 1) == 1) {
                node[r - 1].tag += k;
                node[r - 1].val += ncnt * val;
                rcnt += ncnt;
            }
            l /= 2;
            r /= 2;
            ncnt *= 2;
        }
        while (l) {
            node[l].val += lcnt * val;
            node[r].val += rcnt * val;
            l /= 2;
            r /= 2;
        }
        return;
    }

    lxl Sum(int s, int t) {
        int l = N + s - 1;
        int r = N + t + 1;
        lxl lcnt = 0;
        lxl rcnt = 0;
        lxl ncnt = 1;
        lxl ret = 0;
        while (l / 2 != r / 2) {
            ret += lcnt * node[l].tag;
            ret += rcnt * node[r].tag;
            if ((l & 1) == 0) {
                ret += node[l + 1].val;
                lcnt += ncnt;
            }
            if ((r & 1) == 1) {
                ret += node[r - 1].val;
                rcnt += ncnt;
            }
            l /= 2;
            r /= 2;
            ncnt *= 2;
        }
        while (l) {
            ret += lcnt * node[l].tag;
            ret += rcnt * node[r].tag;
            l /= 2;
            r /= 2;
        }
        return ret;
    }
} SGT;

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i]; SGT.Build();
    for (int i = 1; i <= m; i++) {
        std::cin >> o;
        if (o == 1) {
            std::cin >> x >> y >> k;
            SGT.Add(x, y, k);
        } else if (o == 2) {
            std::cin >> x >> y;
            std::cout << SGT.Sum(x, y) << '\n';
        }
    }
    return 0;
}