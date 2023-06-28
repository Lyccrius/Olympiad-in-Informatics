#include <iostream>
#include <string>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef char chr;
typedef std::string str;

const int maxN = 3e6;
const int maxM = 3e5;
const str s = "switch";
const str c = "count";

int n, m;
chr a[maxN + 10];
str op;
int l, r;

struct SegmentTree {
    struct Node {
        int cnt4;
        int cnt7;
        int lenu;
        int lend;
        int tag;
    } node[4 * maxN + 10];

    void makeTag(int u) {
        std::swap(node[u].cnt4, node[u].cnt7);
        std::swap(node[u].lenu, node[u].lend);
        node[u].tag ^= 1;
        return;
    }

    void pushDown(int u) {
        if (!node[u].tag) return;
        makeTag(2 * u);
        makeTag(2 * u + 1);
        node[u].tag = false;
        return;
    }

    void pushUp(int u) {
        node[u].cnt4 = node[2 * u].cnt4 + node[2 * u + 1].cnt4;
        node[u].cnt7 = node[2 * u].cnt7 + node[2 * u + 1].cnt7;
        node[u].lenu = std::max(node[2 * u].lenu, node[2 * u + 1].lenu);
        node[u].lend = std::max(node[2 * u].lend, node[2 * u + 1].lend);
        node[u].lenu = std::max(node[u].lenu, node[2 * u].cnt4 + node[2 * u + 1].lenu);
        node[u].lenu = std::max(node[u].lenu, node[2 * u].lenu + node[2 * u + 1].cnt7);
        node[u].lend = std::max(node[u].lend, node[2 * u].cnt7 + node[2 * u + 1].lend);
        node[u].lend = std::max(node[u].lend, node[2 * u].lend + node[2 * u + 1].cnt4);
        return;
    }

    void build(int u, int l, int r) {
        if (l == r) {
            if (a[l] == '4') node[u].cnt4 = 1;
            if (a[l] == '7') node[u].cnt7 = 1;
            node[u].lenu = 1;
            node[u].lend = 1;
            return;
        }
        int mid = (l + r) / 2;
        build(2 * u, l, mid);
        build(2 * u + 1, mid + 1, r);
        pushUp(u);
        return;
    }

    void modify(int u, int l, int r, int s, int t) {
        if (s <= l && r <= t) {
            makeTag(u);
            return;
        }
        pushDown(u);
        int mid = (l + r) / 2;
        if (s <= mid) modify(2 * u, l, mid, s, t);
        if (t >= mid + 1) modify(2 * u + 1, mid + 1, r, s, t);
        pushUp(u);
        return;
    }

    int query(int u, int l, int r) {
        return node[u].lenu;
    }
} sgt;

int main() {
    promote();
    std::cin >> n >> m;
    std::cin >> (a + 1);
    sgt.build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        std::cin >> op;
        if (op == s) std::cin >> l >> r, sgt.modify(1, 1, n, l, r);
        if (op == c) std::cout << sgt.query(1, 1, n) << '\n';
    }
    return 0;
}