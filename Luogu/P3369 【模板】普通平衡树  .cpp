#include <iostream>

const int maxN = 1e5;
const int maxX = 1e7;

int n;
int opt, x;

namespace treap {
    struct Node {
        int lson;
        int rson;
        int val;
        int cnt;
        int size;
        int rand;
    } node[maxN + 10];

    int ncnt;

    void pushUp(int u) {
        node[u].size = node[node[u].lson].size + node[node[u].rson].size + node[u].cnt;
        return;
    }

    void rotateL(int &u) {
        int t = node[u].rson;
        node[u].rson = node[t].lson;
        node[t].lson = u;
        pushUp(u);
        pushUp(t);
        u = t;
        return;
    }

    void rotateR(int &u) {
        int t = node[u].lson;
        node[u].lson = node[t].rson;
        node[t].rson = u;
        pushUp(u);
        pushUp(t);
        u = t;
        return;
    }

    void insert(int &u, int val) {
        if (!u) {
            u = ++ncnt;
            node[u].val = val;
            node[u].cnt = 1;
            node[u].size = 1;
            node[u].rand = rand();
            return;
        }
        if (node[u].val == val) node[u].cnt++;
        else if (node[u].val > val) {
            insert(node[u].lson, val);
            if (node[node[u].lson].rand > node[u].rand) rotateR(u);
        } else if (node[u].val < val) {
            insert(node[u].rson, val);
            if (node[node[u].rson].rand > node[u].rand) rotateL(u);
        }
        pushUp(u);
        return;
    }

    void delete_(int &u, int val) {
        if (!u) return;
        if (node[u].val > val) {
            delete_(node[u].lson, val);
        } else if (node[u].val < val) {
            delete_(node[u].rson, val);
        } else {
            if (node[u].cnt > 1) node[u].cnt--;
            else if (!node[u].lson || !node[u].rson) u = node[u].lson + node[u].rson;
            else if (node[node[u].lson].rand > node[node[u].rson].rand) {
                rotateR(u);
                delete_(u, val);
            } else {
                rotateL(u);
                delete_(u, val);
            }
        }
        pushUp(u);
        return;
    }

    int queryRnk(int &u, int val) {
        if (!u) return 1;
        if (node[u].val == val) return node[node[u].lson].size + 1;
        if (node[u].val > val) return queryRnk(node[u].lson, val);
        if (node[u].val < val) return node[node[u].lson].size + node[u].cnt + queryRnk(node[u].rson, val);
    }

    int queryKth(int &u, int k) {
        //printf("queryKth(%d, %d) [val = %d, lsize = %d, cnt = %d]\n", u, k, node[u].val, node[node[u].lson].size, node[u].cnt);
        if (!u) return 0;
        if (node[node[u].lson].size >= k) {
            //printf("turn left\n");
            return queryKth(node[u].lson, k);
        }
        if (node[node[u].lson].size + node[u].cnt >= k) return node[u].val;
        //printf("turn right\n");
        return queryKth(node[u].rson, k - node[node[u].lson].size - node[u].cnt);
    }

    int queryPre(int u, int val) {
        //printf("queryPre(%d, %d), [%d]\n", u, val, node[u].val);
        if (!u) return - maxX;
        if (node[u].val < val) return std::max(node[u].val, queryPre(node[u].rson, val));
        return queryPre(node[u].lson, val);
    }

    int querySuf(int u, int val) {
        //printf("querySuf(%d, %d) [%d]\n", u, val, node[u].val);
        if (!u) return maxX;
        if (node[u].val > val) return std::min(node[u].val, querySuf(node[u].lson, val));
        return querySuf(node[u].rson, val);
    }
}

struct Treap {
    int root;

    void Insert(int val) {
        treap::insert(root, val);
        return;
    }

    void Delete(int val) {
        treap::delete_(root, val);
        return;
    }

    void QueryRnk(int val) {
        std::cout << treap::queryRnk(root, val) << '\n';
        return;
    }

    void QueryKth(int k) {
        std::cout << treap::queryKth(root, k) << '\n';
        return;
    }

    void QueryPre(int val) {
        std::cout << treap::queryPre(root, val) << '\n';
        return;
    }

    void QuerySuf(int val) {
        std::cout << treap::querySuf(root, val) << '\n';
        return;
    }
} T;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> opt >> x;
        if (opt == 1) T.Insert(x);
        if (opt == 2) T.Delete(x);
        if (opt == 3) T.QueryRnk(x);
        if (opt == 4) T.QueryKth(x);
        if (opt == 5) T.QueryPre(x);
        if (opt == 6) T.QuerySuf(x);
    }
    return 0;
}