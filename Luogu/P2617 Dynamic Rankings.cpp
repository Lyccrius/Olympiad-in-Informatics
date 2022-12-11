#include <cstdio>
#include <vector>

const int maxN = 1e5 + 10;
const int maxM = 1e5 + 10;
const int inf = 1e9 + 10;

int n, m;
int a[maxN];
char opt;
int l, r, k;
int x, y;

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

struct Operation {
    int type;
    int l, r;
    int k;
    int id;

    bool operator<(Operation other) const {
        if (l != other.l) return l < other.l;
        return r < other.r;
    }
};

int res[maxM];

void Solve(int l, int r, std::vector<Operation> q) {
    if (l == r - 1) {
        for (int i = 0; i < q.size(); i++) if (q[i].type) res[q[i].id] = l;
        return;
    }
    if (q.empty()) return;
    int mid = (l + r) >> 1;
    std::vector<Operation> q1, q2;
    for (int i = 0; i < q.size(); i++) {
        if (q[i].type) {
            int c = BIT.Ask(q[i].r) - BIT.Ask(q[i].l - 1);
            if (c >= q[i].k) q1.push_back(q[i]);
            else q[i].k -= c, q2.push_back(q[i]);
        } else {
            if (q[i].k < mid) BIT.Add(q[i].l, q[i].r), q1.push_back(q[i]);
            else q2.push_back(q[i]);
        }
    }
    for (int i = 0; i < q1.size(); i++) if (!q1[i].type) BIT.Add(q1[i].l, -q1[i].r);
    Solve(l, mid, q1);
    Solve(mid, r, q2);
    return;
}

int main() {
    std::vector<Operation> q;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), q.push_back((Operation){0, i, 1, a[i]});
    for (int i = 1; i <= m; i++) {
        scanf(" %c", &opt);
        if (opt == 'Q') {
            scanf("%d%d%d", &l, &r, &k);
            q.push_back((Operation){1, l, r, k, i});
        } else {
            scanf("%d%d", &x, &y);
            q.push_back((Operation){0, x, -1, a[x], 0});
            q.push_back((Operation){0, x, 1, y, 0});
            a[x] = y;
        }
    }
    for (int i = 1; i <= m; i++) res[i] = -1;
    Solve(0, inf, q);
    for (int i = 1; i <= m; i++) if (res[i] != -1) printf("%d\n", res[i]);
    return 0;
}