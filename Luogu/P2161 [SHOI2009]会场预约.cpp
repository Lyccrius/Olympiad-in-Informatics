#include <iostream>

typedef char chr;

const int maxN = 2e5;
const int maxA = 1e5;

int n;
chr opt;
int start, end;
int tot;
int cnt;
int del[maxN + 10];

struct SegmentTree {
    struct Node {
        int tag;
        int tav;

        Node() {
            tag = true;
            return;
        }
    } node[4 * maxA + 10];

    void Find(int u, int l, int r, int val) {
        if (node[u].tag) {
            if (del[node[u].tav] == false && node[u].tav) {
                del[node[u].tav] = true;
                tot--;
                cnt++;
            }
            node[u].tav = val;
            return;
        }
        int mid = (l + r) / 2;
        Find(2 * u, l, mid, val);
        Find(2 * u + 1, mid + 1, r, val);
        node[u].tav = val;
        node[u].tag = true;
        return;
    }

    void PushDown(int u) {
        node[u].tag = false;
        if (!node[u].tav) return;
        node[2 * u].tav = node[u].tav;
        node[2 * u + 1].tav = node[u].tav;
        node[u].tav = 0;
        return;
    }

    void Modify(int u, int l, int r, int s, int t, int val) {
        if (s <= l && r <= t) {
            Find(u, l, r, val);
            return;
        }
        PushDown(u);
        int mid = (l + r) / 2;
        if (s <= mid) Modify(2 * u, l, mid, s, t, val);
        if (t >= mid + 1) Modify(2 * u + 1, mid + 1, r, s, t, val);
        return;
    }
} SGT;

void add(int i) {
    std::cin >> start >> end;
    tot++;
    cnt = 0;
    SGT.Modify(1, 1, maxA, start, end, i);
    std::cout << cnt << '\n';
    return;
}

void ask() {
    std::cout << tot << '\n';
    return;
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> opt;
        if (opt == 'A') add(i);
        if (opt == 'B') ask();
    }
    return 0;
}