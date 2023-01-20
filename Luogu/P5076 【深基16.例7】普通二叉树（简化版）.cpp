#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxQ = 1e4;
const int inf = 2147483647;

int q;
int op, x;

struct BinarySearchTree {
    struct Node {
        int val;
        int cnt;
        int size;
        int lson;
        int rson;
    } node[maxQ + 10];

    int ncnt;
    int root;

    int QueryRnk(int u, int val) {
        if (!u) return 1;
        if (node[u].val == val) return node[node[u].lson].size + node[u].cnt;
        if (node[u].val > val) return QueryRnk(node[u].lson, val);
        if (node[u].val < val) return QueryRnk(node[u].rson, val) + node[node[u].lson].size + node[u].cnt;
    }

    int QueryKth(int u, int val) {
        if (val <= node[node[u].lson].size) return QueryKth(node[u].lson, val);
        if (val > node[node[u].lson].size + node[u].cnt) return QueryKth(node[u].rson, val - node[node[u].lson].size - node[u].cnt);
        return node[u].val;
    }

    int QueryPre(int u, int val) {
        int rank = QueryRnk(u, val);
        return QueryKth(u, rank - 1);
    }

    int QuerySuf(int u, int val) {
        int rank = QueryRnk(u, val + 1);
        return QueryKth(u, rank);
    }

    void Insert(int &u, int val) {
        if (!u) {
            u = ++ncnt;
            node[u].val = val;
            node[u].cnt = 1;
            node[u].size = 1;
            return;
        }
        node[u].size++;
        if (node[u].val == val) {
            node[u].cnt++;
            return;
        }
        if (node[u].val > val) Insert(node[u].lson, val);
        else Insert(node[u].rson, val);
        return;
    }
} BST;

int main() {
    //BST.Insert(BST.root, -inf);
    BST.Insert(BST.root, inf);
    std::cin >> q;
    while (q--) {
        std::cin >> op >> x;
        if (op == 1) std::cout << BST.QueryRnk(BST.root, x) << '\n';
        if (op == 2) std::cout << BST.QueryKth(BST.root, x) << '\n';
        if (op == 3) std::cout << BST.QueryPre(BST.root, x) << '\n';
        if (op == 4) std::cout << BST.QuerySuf(BST.root, x) << '\n';
        if (op == 5) BST.Insert(BST.root, x);
    }
    return 0;
}