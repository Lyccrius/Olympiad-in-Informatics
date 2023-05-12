#include <iostream>

#define int long long

const int maxN = 2e5 + 10;
const int mod = 998244353;
const int inv2 = 499122177;

int n, q;
int a[maxN + 10];
int b[maxN + 10];
int opt, x, v;

struct SegmentTree {
    struct Node {
        int res;
        int val;
        int tag;
    } node[4 * maxN + 10];

    void MakeTag(int u, int l, int r, int tag) {
        node[u].res = (node[u].res + 1ll * tag * (r - l + 1) % mod * (r - l + 2) % mod * inv2 % mod) % mod;
        node[u].val = (node[u].val + 1ll * tag * (r - l + 1) % mod) % mod;
        node[u].tag = (node[u].tag + tag) % mod;
        return;
    }

    void PushUp(int u, int l, int r) {
        int mid = (l + r) / 2;
        node[u].val = (node[2 * u].val + node[2 * u + 1].val) % mod;
        node[u].res = (node[2 * u].res + node[2 * u + 1].res + 1ll * (r - mid) * node[2 * u].val % mod) % mod;
        return;
    }
    
    void PushDown(int u, int l, int r) {
        if (!node[u].tag) return;
        int mid = (l + r) / 2;
        MakeTag(2 * u, l, mid, node[u].tag);
        MakeTag(2 * u + 1, mid + 1, r, node[u].tag);
        node[u].tag = 0;
        return;
    }

    void Build(int u, int l, int r) {
        if (l == r) {
            node[u].val = b[l];
            node[u].res = b[l];
        //printf("val[%d, %d] = %d\n", l, r, node[u].val);
        //printf("res[%d, %d] = %d\n", l, r, node[u].res);
            return;
        }
        int mid = (l + r) / 2;
        Build(2 * u, l, mid);
        Build(2 * u + 1, mid + 1, r);
        PushUp(u, l, r);
        //printf("val[%d, %d] = %d\n", l, r, node[u].val);
        //printf("res[%d, %d] = %d\n", l, r, node[u].res);
        return;
    }

    void Add(int u, int l, int r, int s, int t, int val) {
        if (s <= l && r <= t) {
            MakeTag(u, l, r, val);
            return;
        }
        PushDown(u, l, r);
        int mid = (l + r) / 2;
        if (s <= mid) Add(2 * u, l, mid, s, t, val);
        if (t >= mid + 1) Add(2 * u + 1, mid + 1, r, s, t, val);
        PushUp(u, l, r);
        return;
    }

    int Ask(int u, int l, int r, int p) {
        if (r <= p) {
            //printf("[%d, %d]: %d\n", l, r, node[u].res);
            return node[u].res;
        }
        PushDown(u, l, r);
        int mid = (l + r) / 2;
        if (p <= mid) return Ask(2 * u, l, mid, p);
        //printf("[%d, %d]: %d + %d * %d + [%d, %d]\n", l, r, node[2 * u].res, node[2 * u].val, (p - mid), mid + 1, r);
        return (node[2 * u].res + 1ll * node[2 * u].val * (p - mid) % mod + Ask(2 * u + 1, mid + 1, r, p)) % mod;
    }
} SGT;

signed main() {
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) b[i] = (b[i - 1] + a[i]) % mod;
    SGT.Build(1, 1, n);
    for (int i = 1; i <= q; i++) {
        std::cin >> opt;
        if (opt == 1) {
            std::cin >> x >> v;
            SGT.Add(1, 1, n, x, n, - a[x]);
            a[x] = v;
            SGT.Add(1, 1, n, x, n, a[x]);
        } else {
            std::cin >> x;
            std::cout << SGT.Ask(1, 1, n, x) % mod << '\n';
        }
    }
    return 0;
}

/*
    1   2   3
    1   3   6
    1   4   10
*/