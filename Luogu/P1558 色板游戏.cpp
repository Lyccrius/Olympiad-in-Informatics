#include <iostream>

const int maxL = 1e5;
const int maxT = 30;
const int maxO = 1e5;

int L, T, O;
char opt; int A, B, C;

int popcount(int x) {
    int ret = 0;
    while (x) {
        if (x & 1) ret++;
        x >>= 1;
    }
    return ret;
}

struct SegmentTree {
    struct Node {
        int cnt;
        int tag;
    } node[maxL * 4 + 10];

    void MakeTag(int u, int c) {
        node[u].tag = c;
        node[u].cnt = (1 << c);
        return;
    }

    void PushUp(int u) {
        node[u].cnt = node[u * 2].cnt | node[u * 2 + 1].cnt;
        return;
    }

    void PushDown(int u) {
        if (!node[u].tag) return;
        MakeTag(u * 2, node[u].tag);
        MakeTag(u * 2 + 1, node[u].tag);
        node[u].tag = 0;
        return;
    }

    void Build(int u, int l, int r) {
        if (l == r) {
            node[u].cnt = (1 << 1);
            return;
        }
        int mid = (l + r) / 2;
        Build(u * 2, l, mid);
        Build(u * 2 + 1, mid + 1, r);
        PushUp(u);
        return;
    }

    void Modify(int u, int l, int r, int s, int t, int c) {
        if (s <= l && r <= t) {
            MakeTag(u, c);
            return;
        }
        PushDown(u);
        int mid = (l + r) / 2;
        if (s <= mid) Modify(u * 2, l, mid, s, t, c);
        if (t >= mid + 1) Modify(u * 2 + 1, mid + 1, r, s, t, c);
        PushUp(u);
        return;
    }

    int Query(int u, int l, int r, int s, int t) {
        if (s <= l && r <= t) {
            return node[u].cnt;
        }
        PushDown(u);
        int ret = 0;
        int mid = (l + r) / 2;
        if (s <= mid) ret |= Query(u * 2, l, mid, s, t);
        if (t >= mid + 1) ret |= Query(u * 2 + 1, mid + 1, r, s, t);
        return ret;
    }
} SGT;

int main() {
    std::cin >> L >> T >> O;
    SGT.Build(1, 1, L);
    for (int i = 1; i <= O; i++) {
        std::cin >> opt;
        if (opt == 'C') {
            std::cin >> A >> B >> C; if (A > B) std::swap(A, B);
            SGT.Modify(1, 1, L, A, B, C);
        } else if (opt == 'P') {
            std::cin >> A >> B; if (A > B) std::swap(A, B);
            std::cout << popcount(SGT.Query(1, 1, L, A, B)) << '\n';
        }
    }
    return 0;
}