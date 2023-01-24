#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 5e5;
const int maxM = 5e5;
const int inf = 1e9;

int n, m;
int A[maxN + 10];
int B[maxN + 10];
int op;
int x, y;
int l, r;

struct SegmentTree {
    struct Node {
        int lson;
        int rson;
        int maxA;
        int minB;
        int psi;
        int ij;
        int jk;
    } node[maxN * 4 + 10];

    int ncnt;
    int root;

    void PushUp(int u) {
        int lson = node[u].lson;
        int rson = node[u].rson;
        node[u].maxA = std::max(node[lson].maxA, node[rson].maxA);
        node[u].minB = std::min(node[lson].minB, node[rson].minB);
        node[u].psi = std::max(node[lson].psi, node[rson].psi);
        node[u].psi = std::max(node[u].psi, node[lson].ij + node[rson].maxA);
        node[u].psi = std::max(node[u].psi, node[lson].maxA + node[rson].jk);
        node[u].ij = std::max(node[lson].ij, node[rson].ij);
        node[u].ij = std::max(node[u].ij, node[lson].maxA - node[rson].minB);
        node[u].jk = std::max(node[lson].jk, node[rson].jk);
        node[u].jk = std::max(node[u].jk, node[rson].maxA - node[lson].minB);
        return;
    }

    void Build(int &u, int l, int r) {
        u = ++ncnt;
        if (l == r) {
            node[u].maxA = A[l];
            node[u].minB = B[l];
            node[u].psi = -inf;
            node[u].ij = -inf;
            node[u].jk = -inf;
            return;
        }
        int mid = (l + r) / 2;
        Build(node[u].lson, l, mid);
        Build(node[u].rson, mid + 1, r);
        PushUp(u);
        return;
    }

    void ModifyA(int u, int l, int r, int x, int y) {
        if (l == r) {
            node[u].maxA = y;
            return;
        }
        int mid = (l + r) / 2;
        if (x <= mid) ModifyA(node[u].lson, l, mid, x, y);
        else ModifyA(node[u].rson, mid + 1, r, x, y);
        PushUp(u);
    }

    void ModifyB(int u, int l, int r, int x, int y) {
        if (l == r) {
            node[u].minB = y;
            return;
        }
        int mid = (l + r) / 2;
        if (x <= mid) ModifyB(node[u].lson, l, mid, x, y);
        else ModifyB(node[u].rson, mid + 1, r, x, y);
        PushUp(u);
    }

    Node Merge(Node l, Node r) {
        Node ret;
        ret.maxA = std::max(l.maxA, r.maxA);
        ret.minB = std::min(l.minB, r.minB);
        ret.psi = std::max(l.psi, r.psi);
        ret.psi = std::max(ret.psi, l.ij + r.maxA);
        ret.psi = std::max(ret.psi, l.maxA + r.jk);
        ret.ij = std::max(l.ij, r.ij);
        ret.ij = std::max(ret.ij, l.maxA - r.minB);
        ret.jk = std::max(l.jk, r.jk);
        ret.jk = std::max(ret.jk, r.maxA - l.minB);
        return ret;
    }

    Node Query(int u, int l, int r, int s, int t) {
        if (s <= l && r <= t) return node[u];
        int mid = (l + r) / 2;
        if (t <= mid) return Query(node[u].lson, l, mid, s, t);
        if (s > mid) return Query(node[u].rson, mid + 1, r, s, t);
        return Merge(Query(node[u].lson, l, mid, s, t), Query(node[u].rson, mid + 1, r, s, t));
    }
} SGT;

int main() {
    promote();
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> A[i];
    for (int i = 1; i <= n; i++) std::cin >> B[i];
    SGT.Build(SGT.root, 1, n);
    for (int i = 1; i <= m; i++) {
        std::cin >> op;
        if (op == 1) {
            std::cin >> x >> y;
            SGT.ModifyA(SGT.root, 1, n, x, y);
        }
        if (op == 2) {
            std::cin >> x >> y;
            SGT.ModifyB(SGT.root, 1, n, x, y);
        }
        if (op == 3) {
            std::cin >> l >> r;
            std::cout << SGT.Query(SGT.root, 1, n, l, r).psi << '\n';
        }
    }
    return 0;
}