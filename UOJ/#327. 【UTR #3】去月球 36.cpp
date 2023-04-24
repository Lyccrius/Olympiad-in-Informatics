#include "mythological.h"
#include <stack>

typedef std::stack<int> sic;

const int maxN = 1e5;
const int logN = 17;

namespace ns {
    int n;
    int t;
    int a[maxN + 10];
}

namespace subtask {
    namespace _1 {
        void init() {
            return;
        }

        int query(int l, int r) {
            sic s;
            int ret = 0;
            for (int i = l; i <= r; i++) {
                if (s.size() && s.top() == ns::a[i]) {
                    ret += 2;
                    s.pop();
                } else {
                    s.push(ns::a[i]);
                }
            }
            return ret;
        }
    }

    namespace _2 {
        struct SegmentTree {
            struct Node {
                int lson;
                int rson;
                int val;
            } node[maxN * logN + 10];

            int root[maxN + 10];
            int ncnt;

            int Clone(int u) {
                ncnt++;
                node[ncnt] = node[u];
                return ncnt;
            }

            void PushUp(int u) {
                node[u].val = node[node[u].lson].val + node[node[u].rson].val;
                return;
            }

            void Add(int &u, int l, int r, int pos, int val) {
                u = Clone(u);
                if (l == r) {
                    node[u].val += val;
                    return;
                }
                int mid = (l + r) / 2;
                if (pos <= mid) Add(node[u].lson, l, mid, pos, val);
                if (pos >= mid + 1) Add(node[u].rson, mid + 1, r, pos, val);
                PushUp(u);
                return;
            }

            int Ask(int u, int l, int r, int s, int t) {
                if (s <= l && r <= t) {
                    return node[u].val;
                }
                int mid = (l + r) / 2;
                if (t <= mid) return Ask(node[u].lson, l, mid, s, t);
                if (s >= mid + 1) return Ask(node[u].rson, mid + 1, r, s, t);
                return Ask(node[u].lson, l, mid, s, t) + Ask(node[u].rson, mid + 1, r, s, t);
            }
        } SGT;

        void init() {
            sic s;
            SGT.ncnt = 0;
            for (int i = 1; i <= ns::n; i++) {
                SGT.root[i] = SGT.root[i - 1];
                if (s.size() && ns::a[s.top()] == ns::a[i]) {
                    SGT.Add(SGT.root[i], 1, ns::n, s.top(), 2);
                    s.pop();
                } else {
                    s.push(i);
                }
            }
            return;
        }

        int query(int l, int r) {
            return SGT.Ask(SGT.root[r], 1, ns::n, l, r);
        }
    }
}

void init(int n, int m, int a[], int t) {
    ns::n = n;
    ns::t = t;
    for (int i = 1; i <= n; i++) ns::a[i] = a[i];
    if (ns::t == 1) subtask::_1::init();
    if (ns::t == 2) subtask::_2::init();
    return;
}

int query(int l, int r) {
    if (ns::t == 1) return subtask::_1::query(l, r);
    if (ns::t == 2) return subtask::_2::query(l, r);
}