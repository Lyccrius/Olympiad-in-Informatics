#include <iostream>

const int maxN = 1e5;
const int maxM = 1e5;

int n;
int opt, x;

struct Treap {
    struct Node {
        int lson;
        int rson;
        int val;
        int cnt;
        int size;
        int rand;
    } node[maxN + 10];

    int ncnt;
    int root;

    void PushUp(int u) {
        node[u].size = node[node[u].lson].size + node[node[u].rson].size + node[u].cnt;
        return;
    }

    void RotateL(int &u) {
        int t = node[u].rson;
        node[u].rson = node[t].lson;
        node[t].lson = u;
        node[t].size = node[u].size;
        PushUp(u);
        u = t;
        return;
    }

    void RotateR(int &u) {
        int t = node[u].lson;
        node[u].lson = node[t].rson;
        node[t].rson = u;
        node[t].size = node[u].size;
        PushUp(u);
        u = t;
        return;
    }

    void Insert(int &u, int val) {
        if (u == 0) {
            u = ++ncnt;
            node[u].val = val;
            node[u].cnt = 1;
            node[u].size = 1;
            node[u].rand = rand();
            return;
        }
        node[u].size++;
        if (node[u].val == val) {
            node[u].cnt++;
        } else if (node[u].val > val) {
            Insert(node[u].lson, val);
            if (node[node[u].lson].rand < node[u].rand) RotateR(u);
        } else if (node[u].val < val) {
            Insert(node[u].rson, val);
            if (node[node[u].rson].rand < node[u].rand) RotateL(u);
        }
        return;
    }

    void Delete(int &u, int val) {
        if (u == 0) return;
        if (node[u].val == val) {
            if (node[u].cnt > 1) {
                node[u].cnt--;
                node[u].size--;
            } else {
                if (node[u].lson == 0 || node[u].rson == 0) {
                    u = node[u].lson + node[u].rson;
                } else if (node[node[u].lson].rand < node[node[u].rson].rand) {
                    RotateR(u);
                    Delete(u, val);
                } else {
                    RotateL(u);
                    Delete(u, val);
                }
            }
        } else if (node[u].val > val) {
            node[u].size--;
            Delete(node[u].lson, val);
        } else if (node[u].val < val) {
            node[u].size--;
            Delete(node[u].rson, val);
        }
        return;
    }

    int QueryRnk(int u, int val) {
        if (u == 0) return 1;
        if (node[u].val == val) {
            return node[node[u].lson].size + 1;
        } else if (node[u].val > val) {
            return QueryRnk(node[u].lson, val);
        } else if (node[u].val < val) {
            return QueryRnk(node[u].rson, val) + node[node[u].lson].size + node[u].cnt;
        }
    }

    int QueryKth(int u, int k) {
        if (u == 0) return 0;
        if (k <= node[node[u].lson].size) {
            return QueryKth(node[u].lson, k);
        } else if (k > node[node[u].lson].size + node[u].cnt) {
            return QueryKth(node[u].rson, k - node[node[u].lson].size - node[u].cnt);
        } else {
            return node[u].val;
        }
    }
} TP;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> opt >> x;
        if (opt == 1) {
            TP.Insert(TP.root, x);
        } else if (opt == 2) {
            TP.Delete(TP.root, x);
        } else if (opt == 3) {
            std::cout << TP.QueryRnk(TP.root, x) << '\n';
        } else if (opt == 4) {
            std::cout << TP.QueryKth(TP.root, x) << '\n';
        } else if (opt == 5) {
            TP.Insert(TP.root, x);
            std::cout << TP.QueryKth(TP.root, TP.QueryRnk(TP.root, x) - 1) << '\n';
            TP.Delete(TP.root, x);
        } else if (opt == 6) {
            TP.Insert(TP.root, x);
            std::cout << TP.QueryKth(TP.root, TP.QueryRnk(TP.root, x + 1)) << '\n';
            TP.Delete(TP.root, x);
        }
    }
    return 0;
}