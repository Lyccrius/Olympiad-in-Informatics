#include <iostream>
#include <vector>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef std::vector<int> vic;

const int maxN = 5000;
const int maxK = 1000;
const int maxV = 1000000;
const int maxW = 1000;
const int maxQ = 30000;
const int max1 = 10000;
const int p = 1e7 + 19;
const int q = 1e9 + 7;

int n, k, Q;
int v[maxN + max1 + 10], w[maxN + max1 + 10];
int s[maxN + max1 + 10], t[maxN + max1 + 10];
int a[maxQ + 10];
int f[maxK + 10];
int opt, x;

int pow(int a, int b) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = 1ll * ret * a % q;
        a = 1ll * a * a % q;
        b = b / 2;
    }
    return ret;
}

struct SegmentTree {
    struct Node {
        vic qv;
        vic qw;
    } node[4 * maxQ + 10];

    void Modify(int u, int l, int r, int s, int t, int v, int w) {
        if (s <= l && r <= t) {
            node[u].qv.push_back(v);
            node[u].qw.push_back(w);
            return;
        }
        int mid = (l + r) / 2;
        if (s <= mid) Modify(2 * u, l, mid, s, t, v, w);
        if (t >= mid + 1) Modify(2 * u + 1, mid + 1, r, s, t, v, w);
        return;
    }

    void Solve(int u, int l, int r, int *g) {
        int f[maxK + 10];
        for (int i = 0; i <= k; i++) f[i] = g[i];
        for (int i = 0; i < node[u].qv.size(); i++) {
            int v = node[u].qv[i];
            int w = node[u].qw[i];
            for (int j = k; j >= w; j--) {
                f[j] = std::max(f[j], f[j - w] + v);
            }
        }
        if (l == r) {
            if (a[l]) {
                int res = 0;
                int pow = 1;
                for (int m = 1; m <= k; m++) res = (res + 1ll * f[m] * pow % q) % q, pow = 1ll * pow * p % q;
                std::cout << res << '\n';
            }
            return;
        }
        int mid = (l + r) / 2;
        Solve(2 * u, l, mid, f);
        Solve(2 * u + 1, mid + 1, r, f);
        return;
    }
} SGT;

int main() {
    promote();
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) std::cin >> v[i] >> w[i];
    std::cin >> Q;
    for (int i = 1; i <= n + max1; i++) s[i] = 1;
    for (int i = 1; i <= n + max1; i++) t[i] = Q;
    for (int i = 1; i <= Q; i++) {
        std::cin >> opt;
        if (opt == 1) {
            n++;
            std::cin >> v[n] >> w[n];
            s[n] = i;
        } else if (opt == 2) {
            std::cin >> x;
            t[x] = i;
        } else if (opt == 3) {
            a[i] = true;
        }
    }
    for (int i = 1; i <= n; i++) SGT.Modify(1, 1, Q, s[i], t[i], v[i], w[i]);
    SGT.Solve(1, 1, Q, f);
    return 0;
}