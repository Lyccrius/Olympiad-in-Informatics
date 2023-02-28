#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const int maxN = 1e5;
const int maxQ = 1e5;

int n;
int a[maxN + 10];
int q;
int x[maxQ + 10], y[maxQ + 10];


struct SegmentTree {
    struct Node {
        lxl val;
        bool l, r;
    } node[maxN * 4 + 10][2][2];

    void PushUp(int u, int l, int r) {
        int lson = u * 2;
        int rson = u * 2 + 1;
        int mid = (l + r) / 2;
        if (r - l + 1 == 2) {
            node[u][0][0].val = 0;
            node[u][0][0].l = false;
            node[u][0][0].r = false;
            node[u][1][0].val = a[mid];
            node[u][1][0].l = true;
            node[u][1][0].r = true;
            node[u][0][1].val = a[mid + 1];
            node[u][0][1].l = true;
            node[u][0][1].r = true;
            if (a[mid] < a[mid + 1]) {
                node[u][1][1].val = a[mid + 1];
                node[u][1][1].l = false;
                node[u][1][1].r = true;
            } else {
                node[u][1][1].val = a[mid];
                node[u][1][1].l = true;
                node[u][1][1].r = false;
            }
            return;
        }
        //  neither
        if (node[lson][0][1].r + node[rson][1][0].l < 2) {
            node[u][0][0].val = node[lson][0][1].val + node[rson][1][0].val;
            node[u][0][0].l = node[lson][1][0].l;
            node[u][0][0].r = node[rson][0][1].r;
        } else if (a[mid] < a[mid + 1]) {
            node[u][0][0].val = node[lson][0][0].val + node[rson][1][0].val;
            node[u][0][0].l = node[lson][0][0].l;
            node[u][0][0].r = node[rson][1][0].r;
        } else {
            node[u][0][0].val = node[lson][0][1].val + node[rson][0][0].val;
            node[u][0][0].l = node[lson][0][1].l;
            node[u][0][0].r = node[rson][0][0].r;
        }
        //  left
        if (node[lson][1][1].r + node[rson][1][0].l < 2) {
            node[u][1][0].val = node[lson][1][1].val + node[rson][1][0].val;
            node[u][1][0].l = node[lson][1][1].l;
            node[u][1][0].r = node[rson][1][0].r;
        } else if (a[mid] < a[mid + 1]) {
            node[u][1][0].val = node[lson][1][0].val + node[rson][1][0].val;
            node[u][1][0].l = node[lson][1][0].l;
            node[u][1][0].r = node[rson][1][0].r;
        } else {
            node[u][1][0].val = node[lson][1][1].val + node[rson][0][0].val;
            node[u][1][0].l = node[lson][1][1].l;
            node[u][1][0].r = node[rson][0][0].r;
        }
        //  right
        if (node[lson][0][1].r + node[rson][1][1].l < 2) {
            node[u][0][1].val = node[lson][0][1].val + node[rson][1][1].val;
            node[u][0][1].l = node[lson][0][1].l;
            node[u][0][1].r = node[rson][1][1].r;
        } else if (a[mid] < a[mid + 1]) {
            node[u][0][1].val = node[lson][0][0].val + node[rson][1][1].val;
            node[u][0][1].l = node[lson][0][0].l;
            node[u][0][1].r = node[rson][1][1].r;
        } else {
            node[u][0][1].val = node[lson][0][1].val + node[rson][0][1].val;
            node[u][0][1].l = node[lson][0][1].l;
            node[u][0][1].r = node[rson][0][1].r;
        }
        //  both
        if (node[lson][1][1].r + node[rson][1][1].l < 2) {
            node[u][1][1].val = node[lson][1][1].val + node[rson][1][1].val;
            node[u][1][1].l = node[lson][1][1].l;
            node[u][1][1].r = node[rson][1][1].r;
        } else if (a[mid] < a[mid + 1]) {
            node[u][1][1].val = node[lson][1][0].val + node[rson][1][1].val;
            node[u][1][1].l = node[lson][1][0].l;
            node[u][1][1].r = node[rson][1][1].r;
        } else {
            node[u][1][1].val = node[lson][1][1].val + node[rson][0][1].val;
            node[u][1][1].l = node[lson][1][1].l;
            node[u][1][1].r = node[rson][0][1].r;
        }
        return;
    }

    void Build(int u, int l, int r) {
        if (l == r) {
            node[u][1][1].val = a[l];
            node[u][1][1].l = true;
            node[u][1][1].r = true;
            node[u][1][0].val = 0;
            node[u][1][0].l = false;
            node[u][1][0].r = false;
            node[u][0][1].val = 0;
            node[u][0][1].l = false;
            node[u][0][1].r = false;
            node[u][0][0].val = 0;
            node[u][0][0].l = false;
            node[u][0][0].r = false;
            return;
        }
        int mid = (l + r) / 2;
        Build(u * 2, l, mid);
        Build(u * 2 + 1, mid + 1, r);
        PushUp(u, l, r);
        return;
    }

    void Modify(int u, int l, int r, int pos, int val) {
        if (l == r) {
            a[pos] = val;
            node[u][1][1].val = val;
            node[u][1][1].l = true;
            node[u][1][1].r = true;
            node[u][1][0].val = 0;
            node[u][1][0].l = false;
            node[u][1][0].r = false;
            node[u][0][1].val = 0;
            node[u][0][1].l = false;
            node[u][0][1].r = false;
            node[u][0][0].val = 0;
            node[u][0][0].l = false;
            node[u][0][0].r = false;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) Modify(u * 2, l, mid, pos, val);
        if (pos >= mid + 1) Modify(u * 2 + 1, mid + 1, r, pos, val);
        PushUp(u, l, r);
        return;
    }
} SGT;

int main() {
    promote();
    std::cin >> n;
	for (int i = 1 ; i <= n ; i ++) std::cin >> a[i];
    SGT.Build(1, 1, n);
    std::cin >> q;
    for (int i = 1; i <= q; i++) {
        std::cin >> x[i] >> y[i];
        SGT.Modify(1, 1, n, x[i], y[i]);
        std::cout << SGT.node[1][1][1].val << '\n';
    }
	return 0;
}