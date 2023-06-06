#include <iostream>
#include <vector>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;
typedef std::vector<int> vic;
typedef std::pair<int, int> pii;

const int maxN = 5e5;
const int maxQ = 5e5;
const int maxM = 5e5;
const int maxL = 5e5;
const int maxA = maxN + maxQ;
const int logA = 20;

int n, q;
int l, a;
int op;
int x, y;
int m;
int x1, x2, x3;

namespace segmentTree {
    struct Node {
        lxl val;
        int lson;
        int rson;
    } node[maxL * logA + maxQ * logA + 10];

    int ncnt;

    void pushup(int u) {
        node[u].val = node[node[u].lson].val + node[node[u].rson].val;
        return;
    }

    void add(int &u, int l, int r, int pos, int val) {
        if (!u) u = ++ncnt;
        if (l == r) {
            node[u].val += val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) add(node[u].lson, l, mid, pos, val);
        if (pos >= mid + 1) add(node[u].rson, mid + 1, r, pos, val);
        pushup(u);
        return;
    }
    
    int ask(int *q, int n, int l, int r, lxl len) {
        if (l == r) return l;
        int mid = (l + r) / 2;
        lxl lsum = 0;
        lxl rsum = 0;
        for (int i = 1; i <= n; i++) lsum += node[node[q[i]].lson].val;
        for (int i = 1; i <= n; i++) rsum += node[node[q[i]].rson].val;
        if (lsum > len / 2) {
            for (int i = 1; i <= n; i++) q[i] = node[q[i]].lson;
            return ask(q, n, l, mid, len);
        }
        if (rsum > len / 2) {
            for (int i = 1; i <= n; i++) q[i] = node[q[i]].rson;
            return ask(q, n, mid + 1, r, len);
        }
        return -1;
    }

    int merge(int u, int v) {
        if (!u || !v) return u + v;
        node[u].val += node[v].val;
        node[u].lson = merge(node[u].lson, node[v].lson);
        node[u].rson = merge(node[u].rson, node[v].rson);
        return u;
    }
}

namespace linkedList {
    struct Node {
        int val;
        int last;
    } node[maxL + maxQ + 10];

    int ncnt;

    int build(int val) {
        ncnt++;
        node[ncnt].val = val;
        return ncnt;
    }

    void merge(int &u, int v) {
        node[v].last = u;
        u = v;
        return;
    }
}

struct Sequence {
    lxl l;
    int root;
    int st, ed;

    void push(int val) {
        l++;
        segmentTree::add(root, 0, maxA, val, 1);
        int t = linkedList::build(val);
        linkedList::node[t].last = ed;
        ed = t;
        if (!st) st = ed;
        return;
    }

    void pop() {
        l--;
        segmentTree::add(root, 0, maxA, linkedList::node[ed].val, -1);
        ed = linkedList::node[ed].last;
        if (!ed) st = ed;
        return;
    }
} seq[maxN + maxQ + 10];

signed main() {
    promote();
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        std::cin >> l;
        for (int j = 1; j <= l; j++) std::cin >> a, seq[i].push(a);
    }
    for (int i = 1; i <= q; i++) {
        std::cin >> op;
        if (op == 1) {
            std::cin >> x >> y;
            seq[x].push(y);
        }
        if (op == 2) {
            std::cin >> x;
            seq[x].pop();
        }
        if (op == 3) {
            std::cin >> m;
            int q[m + 10];
            lxl len = 0;
            for (int i = 1; i <= m; i++) std::cin >> x, q[i] = seq[x].root, len += seq[x].l;
            std::cout << segmentTree::ask(q, m, 0, maxA, len) << '\n';
        }
        if (op == 4) {
            std::cin >> x1 >> x2 >> x3;
            seq[x3].l = seq[x1].l + seq[x2].l;
            seq[x3].root = segmentTree::merge(seq[x1].root, seq[x2].root);
            if (seq[x1].ed && seq[x2].ed) {
                seq[x3].st = seq[x1].st;
                seq[x3].ed = seq[x2].ed;
                linkedList::node[seq[x2].st].last = seq[x1].ed;
            } else if (seq[x1].ed) {
                seq[x3].st = seq[x1].st;
                seq[x3].ed = seq[x1].ed;
            } else if (seq[x2].ed) {
                seq[x3].st = seq[x2].st;
                seq[x3].ed = seq[x2].ed;
            }
        }
    }
    return 0;
}