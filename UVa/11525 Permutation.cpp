#include <iostream>

const int maxK = 50000;

int t;
int k;
int s[maxK + 10];
int a[maxK + 10];

struct SegmentTree {
    struct Node {
        int val;
    } node[4 * maxK + 10];

    void PushUp(int u) {
        node[u].val = node[2 * u].val + node[2 * u + 1].val;
        return;
    }

    void Build(int u, int l, int r) {
        if (l == r) {
            node[u].val = 1;
            return;
        }
        int mid = (l + r) / 2;
        Build(2 * u, l, mid);
        Build(2 * u + 1, mid + 1, r);
        PushUp(u);
        return;
    }

    void Add(int u, int l, int r, int pos, int val) {
        if (l == r) {
            node[u].val += val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) Add(2 * u, l, mid, pos, val);
        if (pos >= mid + 1) Add(2 * u + 1, mid + 1, r, pos, val);
        PushUp(u);
        return;
    }

    int Ask(int u, int l, int r, int k) {
        if (l == r) return l;
        int mid = (l + r) / 2;
        if (node[2 * u].val >= k) return Ask(2 * u, l, mid, k);
        else return Ask(2 * u + 1, mid + 1, r, k - node[2 * u].val);
    }
} SGT;

void mian() {
    std::cin >> k;
    SGT.Build(1, 1, k);
    for (int i = 1; i <= k; i++) std::cin >> s[i];
    for (int i = 1; i <= k; i++) {
        a[i] = SGT.Ask(1, 1, k, s[i] + 1);
        SGT.Add(1, 1, k, a[i], -1);
    }
    for (int i = 1; i < k; i++) std::cout << a[i] << ' ';
    std::cout << a[k] << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}