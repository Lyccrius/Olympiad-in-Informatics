#include <iostream>

const int maxN = 1e5;
const int maxM = 1e5;

int n, m;
int l, r;

struct FHQTreap {
    struct Node {
        int val;
        int rand;
        int size;
        int flip;
        int lson;
        int rson;
    } node[maxN + 10];

    int ncnt;
    int root;

    void pushdown(int u) {
        if (node[u].flip == false) return;
        std::swap(node[u].lson, node[u].rson);
        if (node[u].lson) node[node[u].lson].flip ^= node[u].flip;
        if (node[u].rson) node[node[u].rson].flip ^= node[u].flip;
        node[u].flip = false;
        return;
    }

    void pushup(int u) {
        node[u].size = node[node[u].lson].size + node[node[u].rson].size + 1;
        return;
    }

    int merge(int u, int v) {
        if (!u || !v) return u + v;
        if (node[u].rand < node[v].rand) {
            pushdown(u);
            node[u].rson = merge(node[u].rson, v);
            pushup(u);
            return u;
        } else {
            pushdown(v);
            node[v].lson = merge(u, node[v].lson);
            pushup(v);
            return v;
        }
    }

    void insert(int val) {
        ncnt++;
        node[ncnt].val = val;
        node[ncnt].rand = rand();
        node[ncnt].size = 1;
        root = merge(root, ncnt);
    }

    void split(int u, int k, int &x, int &y) {
        if (!u) {
            x = 0;
            y = 0;
            return;
        }
        pushdown(u);
        if (node[node[u].lson].size < k) {
            x = u;
            split(node[u].rson, k - node[node[u].lson].size - 1, node[u].rson, y);
        } else {
            y = u;
            split(node[u].lson, k, x, node[u].lson);
        }
        pushup(u);
        return;
    }

    void reverse(int l, int r) {
        int x, y, z;
        split(root, l - 1, x, y);
        split(y, r - l + 1, y, z);
        node[y].flip ^= 1;
        root = merge(x, merge(y, z));
        return;
    }

    void show(int u) {
        if (!u) return;
        pushdown(u);
        show(node[u].lson);
        std::cout << node[u].val << ' ';
        show(node[u].rson);
        return;
    }
} TH;

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) TH.insert(i);
    for (int i = 1; i <= m; i++) {
        std::cin >> l >> r;
        TH.reverse(l, r);
    }
    TH.show(TH.root);
    return 0;
}