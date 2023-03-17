#include <iostream>

typedef char chr;

const int maxN = 30;
const int maxM = 1e5 + 7;
const int maxQ = 1e6 + 7;

int n, m, q;
chr s[maxN + 10];
int opt;
int l, r;
int pos;
chr t[maxN + 10];
int ans;

struct SegmentTree {
    struct Node {
        int val;
    } node[maxM * 4 + 10];

    void PushUp(int u) {
        node[u].val = node[u * 2].val + node[u * 2 + 1].val;
        return;
    }

    void Modify(int u, int l, int r, int pos, int val) {
        if (l == r) {
            node[u].val = val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) Modify(u * 2, l, mid, pos, val);
        if (pos >= mid + 1) Modify(u * 2 + 1, mid + 1, r, pos, val);
        PushUp(u);
        return;
    }

    int Query(int u, int l, int r, int s, int t) {
        if (s <= l && r <= t) {
            return node[u].val;
        }
        int mid = (l + r) / 2;
        if (t <= mid) return Query(u * 2, l, mid, s, t);
        if (s >= mid + 1) return Query(u * 2 + 1, mid + 1, r, s, t);
        return Query(u * 2, l, mid, s, t) + Query(u * 2 + 1, mid + 1, r, s, t);
    }
} SGT[3][maxN + 10];

int main() {
    std::cin >> n >> m >> q;
    for (int i = 1; i <= m; i++) {
        std::cin >> (s + 1);
        for (int j = 1; j <= n; j++) {
            if (s[j] == '0') {
                SGT[0][j].Modify(1, 1, m, i, 1);
            } else if (s[j] == '1') {
                SGT[1][j].Modify(1, 1, m, i, 1);
            } else if (s[j] == '?') {
                SGT[2][j].Modify(1, 1, m, i, 1);
            }
        }
    }
    for (int i = 1; i <= q; i++) {
        std::cin >> opt;
        if (opt == 0) {
            std::cin >> l >> r;
            int res = 1;
            for (int j = 1; j <= n; j++) {
                //printf("SGT[%d][%d].Query(%d, %d) = %d\n", 0, j, l, r, SGT[0][j].Query(1, 1, m, l, r));
                //printf("SGT[%d][%d].Query(%d, %d) = %d\n", 1, j, l, r, SGT[1][j].Query(1, 1, m, l, r));
                //printf("SGT[%d][%d].Query(%d, %d) = %d\n", 2, j, l, r, SGT[2][j].Query(1, 1, m, l, r));
                if (SGT[0][j].Query(1, 1, m, l, r) && SGT[1][j].Query(1, 1, m, l, r)) {
                    res = 0;
                } else if (SGT[2][j].Query(1, 1, m, l, r) == (r - l + 1)) {
                    res *= 2;
                }
            }
            //std::cout << res << '\n';
            ans ^= res;
        } else if (opt == 1) {
            std::cin >> pos;
            std::cin >> (t + 1);
            for (int j = 1; j <= n; j++) {
                SGT[0][j].Modify(1, 1, m, pos, 0);
                SGT[1][j].Modify(1, 1, m, pos, 0);
                SGT[2][j].Modify(1, 1, m, pos, 0);
            }
            for (int j = 1; j <= n; j++) {
                if (t[j] == '0') {
                    SGT[0][j].Modify(1, 1, m, pos, 1);
                } else if (t[j] == '1') {
                    SGT[1][j].Modify(1, 1, m, pos, 1);
                } else if (t[j] == '?') {
                    SGT[2][j].Modify(1, 1, m, pos, 1);
                }
            }
        }
    }
    std::cout << ans;
    return 0;
}