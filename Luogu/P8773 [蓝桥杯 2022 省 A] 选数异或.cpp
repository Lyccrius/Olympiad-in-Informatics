#include <iostream>
#include <algorithm>
#include <map>

typedef std::map<int, int> mii;

const int maxN = 1e5;
const int maxM = 1e5;

int n, m, x;
int A[maxN + 10];
int l[maxM + 10], r[maxM + 10];

mii appear;
mii other;

struct SegmentTree {
    struct Node {
        int val;
    } node[maxN * 4 + 10];

    void PushUp(int u) {
        node[u].val = std::max(node[u * 2].val, node[u * 2 + 1].val);
        return;
    }

    void Build(int u, int l, int r) {
        if (l == r) {
            node[u].val = other[l];
            return;
        }
        int mid = (l + r) / 2;
        Build(u * 2, l, mid);
        Build(u * 2 + 1, mid + 1, r);
        PushUp(u);
        return;
    }

    int Query(int u, int l, int r, int s, int t) {
        if (s <= l && r <= t) return node[u].val;
        int mid = (l + r) / 2;
        if (t <= mid) return Query(u * 2, l, mid, s, t);
        if (s >= mid + 1) return Query(u * 2 + 1, mid + 1, r, s, t);
        return std::max(Query(u * 2, l, mid, s, t), Query(u * 2 + 1, mid + 1, r, s, t));
    }
} SGT;

int main() {
    std::cin >> n >> m >> x;
    for (int i = 1; i <= n; i++) std::cin >> A[i];
    for (int i = 1; i <= n; i++) {
        other[i] = appear[x ^ A[i]];
        appear[A[i]] = i;
    }
    SGT.Build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        std::cin >> l[i] >> r[i];
        if (SGT.Query(1, 1, n, l[i], r[i]) >= l[i]) std::cout << "yes" << '\n';
        else std::cout << "no" << '\n';
    }
    return 0;
}