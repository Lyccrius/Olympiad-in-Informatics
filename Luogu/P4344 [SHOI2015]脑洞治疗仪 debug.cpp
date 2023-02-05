#include <iostream>
#include <algorithm>
#include <deque>

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

//int cnt;

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

    friend Node operator+(const Node &a, const Node &b) {
        Node ret;
        ret.len = a.len + b.len;
        ret.sum = a.sum + b.sum;
        ret.pre = a.pre;
        ret.suf = b.suf;
        if (a.pre == a.len) ret.pre = a.len + b.pre;
        if (b.suf == b.len) ret.suf = a.suf + b.len;
        ret.res = std::max(a.res, b.res);
        ret.res = std::max(ret.res, a.suf + b.pre);
        ret.res = std::max(ret.res, ret.pre);
        ret.res = std::max(ret.res, ret.suf);
        ret.tag = 0;
        ret.tav = 0;
        return ret;
    }

    int ncnt;
    int root;

    void MakeTag(int u, int val) {
        //printf("MakeTag(%d, %d)\n", u, val);
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
        node[u] = node[l] + node[r];
        node[u].lson = l;
        node[u].rson = r;
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
        //for (int i = 1; i <= cnt; i++) printf("-");
        //printf("Dig(%d, %d, %d, %d, %d)\n", l, r, s, t, val);
        if (s > r || l > t) {
        //    printf("out of limit\n");
            return;
        }
        if (s <= l && r <= t) {
        //    cnt++;
            MakeTag(u, val);
        //    cnt--;
        //    printf("return\n");
            return;
        }
        int mid = (l + r) / 2;
        //cnt++;
        PushDown(u);
        Dig(node[u].lson, l, mid, s, t, val);
        Dig(node[u].rson, mid + 1, r, s, t, val);
        PushUp(u);
        //cnt--;
        return;
    }

    int Ask0(int u, int l, int r, int s, int t) {
        //for (int i = 1; i <= cnt; i++) printf("-");
        //printf("Ask0(%d, %d, %d, %d)\n", l, r, s, t);
        if (s > r || l > t) {
        //    printf("out of limit\n");
            return 0;
        }
        if (s <= l && r <= t) {
        //    printf("return %d\n", node[u].len - node[u].sum);
            return node[u].len - node[u].sum;
        }
        int mid = (l + r) / 2;
        //cnt++;
        PushDown(u);
        //cnt--;
        //cnt++;
        int ret = Ask0(node[u].lson, l, mid, s, t) + Ask0(node[u].rson, mid + 1, r, s, t);
        //cnt--;
        //printf("return %d\n", ret);
        return ret;
    }

    int Ask1(int u, int l, int r, int s, int t) {
        //for (int i = 1; i <= cnt; i++) printf("-");
        //printf("Ask1(%d, %d, %d, %d)\n", l, r, s, t);
        if (s > r || l > t) {
        //    printf("out of limit\n");
            return 0;
        }
        if (s <= l && r <= t) {
        //    printf("return %d\n", node[u].sum);
            return node[u].sum;
        }
        int mid = (l + r) / 2;
        //cnt++;
        PushDown(u);
        //cnt--;
        //cnt++;
        int ret = Ask1(node[u].lson, l, mid, s, t) + Ask1(node[u].rson, mid + 1, r, s, t);
        //cnt--;
        //printf("return %d\n", ret);
        return ret;
    }

    /*

    struct N4F {
        int u;
        int l, r;
    };

    typedef std::deque<N4F> dnf;

    dnf Split(int l, int r) {
        //for (int i = 1; i <= cnt; i++) printf("-");
        //printf("Split %d, %d\n", l, r);
        dnf ret;
        dnf q;
        q.push_back((N4F) {root, 1, n});
        while (!q.empty()) {
            N4F t = q.front();
            q.pop_front();
            int mid = (t.l + t.r) / 2;
            if (l <= t.l && t.r <= r) {
        //        printf("%d, %d\n", t.l, t.r);
                ret.push_back(t);
            }
            else {
                if (r >= mid + 1) q.push_front((N4F) {node[t.u].rson, mid + 1, t.r});
                if (l <= mid) q.push_front((N4F) {node[t.u].lson, t.l, mid});
            }
        }
        return ret;
    }

    int AskX(dnf q, int x) {
        //for (int i = 1; i <= cnt; i++) printf("-");
        //printf("AskX(%d)\n", x);
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
         *
            if (node[u].len - node[u].sum == x) {
                printf("return %d\n", r);
                return r;
            }
            int mid = (l + r) / 2;
            cnt++;
            PushDown(u);
            cnt--;
            int t = node[node[u].lson].len - node[node[u].lson].sum;
            cnt++;
            int ret;
            if (t <= x) ret = AskX(node[u].lson, l, mid, x);
            else ret = AskX(node[u].rson, mid + 1, r, t - x);
            cnt--;
            printf("return %d\n", ret);
            return ret;
        *
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
        int ret = Fill(node[u].rson, mid + 1, r, s, t, Fill(node[u].lson, l, mid, s, t, x));
        PushUp(u);
        return ret;
    }

    void Fix(int l0, int r0, int l1, int r1) {
        //for (int i = 1; i <= cnt; i++) printf("-");
        //printf("Fix(%d, %d, %d, %d)\n", l0, r0, l1, r1);
        //cnt++;
        int x = Ask1(root, 1, n, l0, r0);
        //cnt--;
        //for (int i = 1; i <= cnt; i++) printf("-");
        //printf("1 of [%d, %d] is %d\n", l0, r0, x);
        if (x == 0) return;
        //cnt++;
        /*
        Dig(root, 1, n, l0, r0, 0);
        Dig(root, 1, n, l1, AskX(Split(l1, r1), x), 1);
        */
        Dig(root, 1, n, l0, r0, 0);
        Fill(root, 1, n, l1, r1, x);
        //cnt--;
        return;
    }

    int Ask(int u, int l, int r, int s, int t) {
        //for (int i = 1; i <= cnt; i++) printf("-");
        //printf("Ask(%d, %d, %d, %d)\n", l, r, s, t);
        if (s > r || l > t) {
        //    printf("out of limit\n");
            //return (Node) {0, 0, 0, 0, 0, 0, 0, 0, 0};
            return 0;
        }
        if (s <= l && r <= t) {
        //    printf("return\n");
            return node[u].res;
        }
        int mid = (l + r) / 2;
        //cnt++;
        PushDown(u);
        //cnt--;
        //cnt++;
        //Node ret = Ask(node[u].lson, l, mid, s, t) + Ask(node[u].rson, mid + 1, r, s, t);
        int ret;
        ret = std::min(node[node[u].lson].suf, mid - s + 1) + std::min(node[node[u].rson].pre, t - mid);
        ret = std::max(ret, Ask(node[u].lson, l, mid, s, t));
        ret = std::max(ret, Ask(node[u].rson, mid + 1, r, s, t));
        //cnt--;
        //printf("return\n");
        return ret;
    }
} SGT;

int main() {
    std::cin >> n >> m;
    SGT.Build(SGT.root, 1, n);
    for (int i = 1; i <= m; i++) {
        //cnt++;
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
        //cnt--;
    }
    return 0;
}