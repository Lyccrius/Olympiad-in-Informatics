#include <iostream>

const int maxN = 1e5;
const int maxX = 1e7;

int n;
int opt, x;

struct FHQTreap {
    struct Node {
        int val;
        int lson;
        int rson;
        int size;
        int rand;
    } node[maxN + 10];

    int ncnt;
    int root;

    void pushup(int u) {
        node[u].size = node[node[u].lson].size + node[node[u].rson].size + 1;
        return;
    }

    void split(int u, int k, int &x, int &y) {
        if (!u) {
            x = 0;
            y = 0;
            return;
        }
        if (node[u].val <= k) {
            x = u;
            split(node[u].rson, k, node[u].rson, y);
        } else {
            y = u;
            split(node[u].lson, k, x, node[u].lson);
        }
        pushup(u);
        return;
    }

    int merge(int u, int v) {
        if (!u || !v) return u + v;
        if (node[u].rand < node[v].rand) {
            node[u].rson = merge(node[u].rson, v);
            pushup(u);
            return u;
        } else {
            node[v].lson = merge(u, node[v].lson);
            pushup(v);
            return v;
        }
    }

    void insert(int val) {
        ncnt++;
        node[ncnt].val = val;
        node[ncnt].size = 1;
        node[ncnt].rand = rand();
        int x, y;
        split(root, val, x, y);
        root = merge(merge(x, ncnt), y);
        return;
    }

    void del(int val) {
        int x, y, z;
        split(root, val, x, y);
        split(x, val - 1, x, z);
        z = merge(node[z].lson, node[z].rson);
        root = merge(merge(x, z), y);
        return;
    }

    void queryRnk(int val) {
        int x, y;
        split(root, val - 1, x, y);
        std::cout << node[x].size + 1 << '\n';
        root = merge(x, y);
        return;
    }

    void queryKth(int u, int k) {
        while (true) {
            if (k <= node[node[u].lson].size) u = node[u].lson;
            else if (k == node[node[u].lson].size + 1) {
                std::cout << node[u].val << '\n';
                return;
            } else {
                k -= node[node[u].lson].size + 1;
                u = node[u].rson;
            }
        }
        return;
    }

    void queryPre(int val) {
        int x, y;
        split(root, val - 1, x, y);
        queryKth(x, node[x].size);
        root = merge(x, y);
        return;
    }

    void querySuf(int val) {
        int x, y;
        split(root, val, x, y);
        queryKth(y, 1);
        root = merge(x, y);
        return;
    }
} FHQTH;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> opt >> x;
        if (opt == 1) FHQTH.insert(x);
        if (opt == 2) FHQTH.del(x);
        if (opt == 3) FHQTH.queryRnk(x);
        if (opt == 4) FHQTH.queryKth(FHQTH.root, x);
        if (opt == 5) FHQTH.queryPre(x);
        if (opt == 6) FHQTH.querySuf(x);
    }
    return 0;
}