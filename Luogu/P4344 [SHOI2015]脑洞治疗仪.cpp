#include <iostream>
#include <algorithm>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 2e5;
const int maxM = 2e5;

int n, m;
int op;
int l, r;
int l0, r0;
int l1, r1;

struct SegmentTree {
    struct Node {
        int lson;
        int rson;
        int len;
        int sum;
        int pre;
        int suf;
        int res;
        int tag;
        int tav;
    } node[maxN * 4 + 10];

    int ncnt;
    int root;

    void MakeTag(int u, int val) {
        if (val) {
            node[u].sum = node[u].len;
            node[u].pre = 0;
            node[u].suf = 0;
            node[u].res = 0;
            node[u].tag = true;
            node[u].tav = 1;
        } else {
            node[u].sum = 0;
            node[u].pre = node[u].len;
            node[u].suf = node[u].len;
            node[u].res = node[u].len;
            node[u].tag = true;
            node[u].tav = 0;
        }
        return;
    }

    void PushUp(int u) {
        int l = node[u].lson;
        int r = node[u].rson;
        node[u].len = node[l].len + node[r].len;
        node[u].sum = node[l].sum + node[r].sum;
        node[u].pre = node[l].pre;
        node[u].suf = node[r].suf;
        if (node[l].pre == node[l].len) node[u].pre = node[l].len + node[r].pre;
        if (node[r].suf == node[r].len) node[u].suf = node[l].suf + node[r].len;
        node[u].res = std::max(node[l].res, node[r].res);
        node[u].res = std::max(node[u].res, node[l].suf + node[r].pre);
        node[u].res = std::max(node[u].res, node[u].pre);
        node[u].res = std::max(node[u].res, node[u].suf);
        node[u].tag = 0;
        node[u].tav = 0;
        return;
    }

    void PushDown(int u) {
        if (!node[u].tag) return;
        MakeTag(node[u].lson, node[u].tav);
        MakeTag(node[u].rson, node[u].tav);
        node[u].tag = false;
        node[u].tav = 0;
        return;
    }

    void Build(int &u, int l, int r) {
        u = ++ncnt;
        if (l == r) {
            node[u].sum = 1;
            node[u].len = 1;
            return;
        }
        int mid = (l + r) / 2;
        Build(node[u].lson, l, mid);
        Build(node[u].rson, mid + 1, r);
        PushUp(u);
        return;
    }

    void Dig(int u, int l, int r, int s, int t, int val) {
        if (s > r || l > t) return;
        if (s <= l && r <= t) {
            MakeTag(u, val);
            return;
        }
        int mid = (l + r) / 2;
        PushDown(u);
        Dig(node[u].lson, l, mid, s, t, val);
        Dig(node[u].rson, mid + 1, r, s, t, val);
        PushUp(u);
        return;
    }

    int Ask0(int u, int l, int r, int s, int t) {
        if (s > r || l > t) return 0;
        if (s <= l && r <= t) return node[u].len - node[u].sum;
        int mid = (l + r) / 2;
        PushDown(u);
        return Ask0(node[u].lson, l, mid, s, t) + Ask0(node[u].rson, mid + 1, r, s, t);
    }

    int Ask1(int u, int l, int r, int s, int t) {
        if (s > r || l > t) return 0;
        if (s <= l && r <= t) return node[u].sum;
        int mid = (l + r) / 2;
        PushDown(u);
        return Ask1(node[u].lson, l, mid, s, t) + Ask1(node[u].rson, mid + 1, r, s, t);
    }

    /*
    struct N4F {
        int u;
        int l, r;
    };

    typedef std::deque<N4F> dnf;

    dnf Split(int l, int r) {
        dnf ret;
        dnf q;
        q.push_back((N4F) {root, 1, n});
        while (!q.empty()) {
            N4F t = q.front();
            q.pop_front();
            int mid = (t.l + t.r) / 2;
            if (l <= t.l && t.r <= r) ret.push_back(t);
            else {
                if (r >= mid + 1) q.push_front((N4F) {node[t.u].rson, mid + 1, t.r});
                if (l <= mid) q.push_front((N4F) {node[t.u].lson, t.l, mid});
            }
        }
        return ret;
    }

    int AskX(dnf q, int x) {
        int ret = q.back().r;
        while (!q.empty()) {
            N4F t = q.front();
            q.pop_front();
            int mid = (t.l + t.r) / 2;
            int d = node[t.u].len - node[t.u].sum;
            if (d < x) x -= d;
            else {
                q.push_front((N4F) {node[t.u].rson, mid + 1, t.r});
                q.push_front((N4F) {node[t.u].lson, t.l, mid});
                if (t.l == t.r) return t.r;
            }
        }
        return ret;
    }
    */

    int Fill(int u, int l, int r, int s, int t, int x) {
        if (s > r || l > t || x == 0) return x;
        int d = node[u].len - node[u].sum;
        if (s <= l && r <= t) {
            if (x >= d) {
                MakeTag(u, 1);
                return x - d;
            }
        }
        int mid = (l + r) / 2;
        PushDown(u);
        int ret;
        if (t <= mid) ret = Fill(node[u].lson, l, mid, s, t, x);
        else if (s >= mid + 1) ret = Fill(node[u].rson, mid + 1, r, s, t, x);
        else ret = Fill(node[u].rson, mid + 1, r, s, t, Fill(node[u].lson, l, mid, s, t, x));
        PushUp(u);
        return ret;
    }

    void Fix(int l0, int r0, int l1, int r1) {
        int x = Ask1(root, 1, n, l0, r0);
        if (x == 0) return;
        Dig(root, 1, n, l0, r0, 0);
        Fill(root, 1, n, l1, r1, x);
        return;
    }

    int Ask(int u, int l, int r, int s, int t) {
        if (s > r || l > t) return 0;
        if (s <= l && r <= t) return node[u].res;
        int mid = (l + r) / 2;
        PushDown(u);
        int ret;
        ret = std::min(node[node[u].lson].suf, mid - s + 1) + std::min(node[node[u].rson].pre, t - mid);
        ret = std::max(ret, Ask(node[u].lson, l, mid, s, t));
        ret = std::max(ret, Ask(node[u].rson, mid + 1, r, s, t));
        return ret;
    }
} SGT;

int main() {
    std::cin >> n >> m;
    SGT.Build(SGT.root, 1, n);
    for (int i = 1; i <= m; i++) {
        std::cin >> op;
        if (op == 0) {
            std::cin >> l >> r;
            SGT.Dig(SGT.root, 1, n, l, r, 0);
        }
        if (op == 1) {
            std::cin >> l0 >> r0 >> l1 >> r1;
            SGT.Fix(l0, r0, l1, r1);
        }
        if (op == 2) {
            std::cin >> l >> r;
            std::cout << SGT.Ask(SGT.root, 1, n, l, r) << '\n';
        }
    }
    return 0;
}