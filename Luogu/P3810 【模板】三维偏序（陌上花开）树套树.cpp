#include <iostream>
#include <algorithm>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1e5;
const int maxK = 2e5;
const int logN = 17;
const int logK = 18;

int n, k;
struct Element {
    int a, b, c;
    int id;

    bool operator<(const Element &other) const {
        if (a != other.a) return a < other.a;
        if (b != other.b) return b < other.b;
        return c < other.c;
    }
} e[maxN + 10];
int f[maxN + 10];
int d[maxN + 10];

struct BinaryIndexedTree {
    struct SegmentTree {
        struct Node {
            int lson;
            int rson;
            int value;
        } node[maxK * logK * logN + 10];

        int ncnt;
        int root[maxK + 10];

        void PushUp(int u) {
            node[u].value = node[node[u].lson].value + node[node[u].rson].value;
            return;
        }

        void Build(int &u) {
            u = ++ncnt;
            return;
        }

        void Modify(int &u, int l, int r, int weight, int value) {
            if (!u) Build(u);
            if (l == r) {
                node[u].value += value;
                return;
            }
            int mid = (l + r) / 2;
            if (weight <= mid) Modify(node[u].lson, l, mid, weight, value);
            else Modify(node[u].rson, mid + 1, r, weight, value);
            PushUp(u);
            return;
        }

        int Query(int u, int l, int r, int weight) {
            if (l == r) return node[u].value;
            int mid = (l + r) / 2;
            if (weight <= mid) return Query(node[u].lson, l, mid, weight);
            else return node[node[u].lson].value + Query(node[u].rson, mid + 1, r, weight);
        }
    } SGT;

    int lowbit(int x) {
        return x & -x;
    }

    void Add(int pos, int weight, int value) {
        for (int i = pos; i <= k; i += lowbit(i)) {
            SGT.Modify(SGT.root[i], 1, k, weight, value);
        }
        return;
    }

    int Ask(int pos, int weight) {
        int ret = 0;
        for (int i = pos; i > 0; i -= lowbit(i)) {
            ret += SGT.Query(SGT.root[i], 1, k, weight);
        }
        //printf("BIT.Ask(%d, %d) = %d\n", pos, weight, ret);
        return ret;
    }
} BIT;

int main() {
    promote();
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) std::cin >> e[i].a >> e[i].b >> e[i].c;
    for (int i = 1; i <= n; i++) e[i].id = i;
    std::sort(e + 1, e + n + 1);
    int i = 1;
    int j;
    while (i <= n) {
        j = i;
        while (e[i].a == e[j].a) BIT.Add(e[j].b, e[j].c, 1), j++;
        j = i;
        while (e[i].a == e[j].a) f[e[j].id] = BIT.Ask(e[j].b, e[j].c), j++;
        i = j;
    }
    for (int i = 1; i <= n; i++) d[f[i]]++;
    for (int i = 1; i <= n; i++) std::cout << d[i] << '\n';
    return 0;
}