#include <iostream>

typedef long long lxl;

const int maxH = 1000;
const int maxW = 1000;
const int logW = 10;

int h, w, h1, w1, h2, w2;
lxl a[maxH + 10][maxW + 10];
lxl b[maxH + 10][maxW + 10];
lxl c[maxH + 10][maxW + 10];
lxl d[maxH + 10][maxW + 10];
lxl ans;

struct SparseTable {
    lxl f[maxW + 10][logW + 5];
    int log[maxW + 10];

    void Build() {
        log[1] = 0;
        for (int j = 2; j <= w; j++) log[j] = log[j / 2] + 1;
        for (int p = 1; p <= logW; p++) for (int j = 1; j <= w; j++) f[j][p] = std::max(f[j][p - 1], f[j + (1 << (p - 1))][p - 1]);
        return;
    }

    lxl Query(int l, int r) {
        int p = log[r - l + 1];
        return std::max(f[l][p], f[r - (1 << p) + 1][p]);
    }
};

struct SegmentTree {
    SparseTable node[4 * maxH + 10];

    void PushUp(int u) {
        int l = 2 * u;
        int r = 2 * u + 1;
        for (int j = 1; j <= w; j++) node[u].f[j][0] = std::max(node[l].f[j][0], node[r].f[j][0]);
        node[u].Build();
        return;
    }

    void Build(int u, int l, int r) {
        if (l == r) {
            for (int j = 1; j <= w; j++) node[u].f[j][0] = d[l][j];
            node[u].Build();
            return;
        }
        int mid = (l + r) / 2;
        Build(2 * u, l, mid);
        Build(2 * u + 1, mid + 1, r);
        PushUp(u);
    }

    lxl Query(int u, int l, int r, int s1, int t1, int s2, int t2) {
        if (s1 <= l && r <= t1) return node[u].Query(s2, t2);
        int mid = (l + r) / 2;
        if (t1 <= mid) return Query(2 * u, l, mid, s1, t1, s2, t2);
        if (s1 >= mid + 1) return Query(2 * u + 1, mid + 1, r, s1, t1, s2, t2);
        return std::max(Query(2 * u, l, mid, s1, t1, s2, t2), Query(2 * u + 1, mid + 1, r, s1, t1, s2, t2));
    }
} SGT;

int main() {
    std::cin >> h >> w >> h1 >> w1 >> h2 >> w2;
    h2 = std::min(h1, h2);
    w2 = std::min(w1, w2);
    for (int i = 1; i <= h; i++) for (int j = 1; j <= w; j++) std::cin >> a[i][j];
    for (int i = 1; i <= h; i++) for (int j = 1; j <= w; j++) b[i][j] = b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1] + a[i][j];
    for (int i = 1; i + h1 - 1 <= h; i++) for (int j = 1; j + w1 - 1 <= w; j++) c[i][j] = b[i + h1 - 1][j + w1 - 1] - b[i - 1][j + w1 - 1] - b[i + h1 - 1][j - 1] + b[i - 1][j - 1];
    for (int i = 1; i + h2 - 1 <= h; i++) for (int j = 1; j + w2 - 1 <= w; j++) d[i][j] = b[i + h2 - 1][j + w2 - 1] - b[i - 1][j + w2 - 1] - b[i + h2 - 1][j - 1] + b[i - 1][j - 1];
    SGT.Build(1, 1, h);
    /*
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            printf("%4d", d[i][j]);
        }
        printf("\n");
    }
    */
    for (int i = 1; i + h1 - 1 <= h; i++) for (int j = 1; j + w1 - 1 <= w; j++) ans = std::max(ans, c[i][j] - SGT.Query(1, 1, h, i, i + h1 - h2, j, j + w1 - w2));
    std::cout << ans << '\n';
    return 0;
}