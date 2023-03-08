#include <iostream>
#include <algorithm>

typedef long long lxl;

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1e5;
const int maxM = 5e4;

int n, m;
int a[maxN + 10];
int b[maxN + 10];
int c[maxN + 10];

struct Node {
    int p;
    int v;
    int t;

    bool operator<(const Node &other) const {
        return v < other.v;
    }
} node[maxN + 10];

struct BinaryIndexedTree {
    struct Node {
        int val;
    } node[maxN + 10];

    int lowbit(int x) {
        return x & - x;
    }

    void Add(int pos, int val) {
        while (pos <= n) {
            node[pos].val += val;
            pos += lowbit(pos);
        }
        return;
    }

    int Ask(int pos) {
        int ret = 0;
        while (pos >= 1) {
            ret += node[pos].val;
            pos -= lowbit(pos);
        }
        return ret;
    }
} BIT;

lxl res[maxM + 10];
lxl ans;

void CDQ(int l, int r) {
    if (l == r) return;
    int mid = (l + r) / 2;
    int i, j;
    CDQ(l, mid);
    CDQ(mid + 1, r);
    std::sort(node + l, node + mid + 1);
    std::sort(node + mid + 1, node + r + 1);
    i = l;
    j = mid + 1;
    while (i <= mid) {
        while (j <= r && node[i].v > node[j].v) {
            BIT.Add(node[j].t, 1);
            j++;
        }
        res[node[i].t] += BIT.Ask(m + 1) - BIT.Ask(node[i].t);
        i++;
    }
    i = l;
    j = mid + 1;
    while (i <= mid) {
        while (j <= r && node[i].v > node[j].v) {
            BIT.Add(node[j].t, - 1);
            j++;
        }
        i++;
    }
    i = mid;
    j = r;
    while (j >= mid + 1) {
        while (i >= l && node[i].v > node[j].v) {
            BIT.Add(node[i].t, 1);
            i--;
        }
        res[node[j].t] += BIT.Ask(m + 1) - BIT.Ask(node[j].t);
        j--;
    }
    i = mid;
    j = r;
    while (j >= mid + 1) {
        while (i >= l && node[i].v > node[j].v) {
            BIT.Add(node[i].t, - 1);
            i--;
        }
        j--;
    }
    return;
}

int main() {
    promote();
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= m; i++) std::cin >> b[i];
    for (int i = 1; i <= n; i++) c[a[i]] = i;
    for (int i = 1; i <= n; i++) node[i].p = i;
    for (int i = 1; i <= n; i++) node[i].v = a[i];
    for (int i = 1; i <= m; i++) node[c[b[i]]].t = i;
    for (int i = 1; i <= n; i++) if (node[i].t == 0) node[i].t = m + 1;
    for (int i = 1; i <= n; i++) ans += BIT.Ask(n) - BIT.Ask(node[i].v), BIT.Add(node[i].v, 1);
    for (int i = 1; i <= n; i++) BIT.Add(node[i].v, - 1);
    CDQ(1, n);
    for (int i = 1; i <= m; i++) std::cout << ans << '\n', ans -= res[i];
    return 0;
}