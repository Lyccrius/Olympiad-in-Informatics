#include <cstdio>
#include <algorithm>
#include <vector>

const int maxN = 3e5 + 10;
const int maxM = 5e4 + 10;

int n, m;
int a[maxN];
int b[maxN];
int c[maxN];
int l, r, k;

struct Query {
    int type;
    int l, r, k;
    int id;
};

struct BinaryIndexedTree {
    struct Node {
        int val;
    } node[maxN];

    int lowbit(int x) {
        return x & -x;
    }

    void Add(int pos, int val) {
        while (pos <= n) {
            node[pos].val += val;
            pos += lowbit(pos);
        }
        return;
    }

    int Ask(int pos) {
        int res = 0;
        while (pos > 0) {
            res += node[pos].val;
            pos -= lowbit(pos);
        }
        return res;
    }
} BIT;

int res[maxM];

void Solve(int l, int r, std::vector<Query> q) {
    if (l == r) {
        for (int i = 0; i < q.size(); i++) res[q[i].id] = l;
        return;
    }
    if (q.empty()) return;
    int mid = (l + r) >> 1;
    std::vector<Query> q1, q2;
    for (int i = 0; i < q.size(); i++) {
        if (q[i].type) {
            int c = BIT.Ask(q[i].r) - BIT.Ask(q[i].l - 1);
            if (c >= q[i].k) q1.push_back(q[i]);
            else q[i].k -= c, q2.push_back(q[i]);
        } else {
            if (q[i].k <= mid) {
                BIT.Add(q[i].l, q[i].r);
                q1.push_back(q[i]);
            } else {
                q2.push_back(q[i]);
            }
        }
    }
    for (int i = 0; i < q1.size(); i++) if (!q1[i].type) BIT.Add(q1[i].l, -q1[i].r);
    Solve(l, mid, q1);
    Solve(mid + 1, r, q2);
    return;
}

int main() {
    std::vector<Query> q;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) b[i] = a[i];
    std::sort(b + 1, b + n + 1);
    int tot = std::unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i <= n; i++) {
        int aa = std::lower_bound(b + 1, b + tot + 1, a[i]) - b;
        q.push_back((Query){0, i, 1, aa, 0});
    }
    for (int i = 1; i <= m; i++) scanf("%d%d%d", &l, &r, &k), q.push_back((Query){1, l, r, k, i});
    Solve(1, maxN, q);
    for (int i = 1; i <= m; i++) printf("%d\n", b[res[i]]);
    return 0;
}