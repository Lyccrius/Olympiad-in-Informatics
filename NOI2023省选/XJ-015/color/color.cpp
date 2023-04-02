#include <iostream>

const int maxC = 5;
const int maxN = 50;
const int maxT = 50;
const int maxM = 200;

const int mod = 998244353;

int C;
int n, m, t;
int a[maxN + 10];
int c[maxN + 10];
int cnt;
int res;
int sum;
int tot;
int ans;

struct SegmentTree {
    struct Node {
        int val;
    } node[maxM * 4 + 10];

    void PushUp(int u) {
        node[u].val = node[u * 2].val + node[u * 2 + 1].val;
        return;
    }

    void Add(int u, int l, int r, int pos, int val) {
        if (l == r) {
            node[u].val += val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) Add(u * 2, l, mid, pos, val);
        if (pos >= mid + 1) Add(u * 2 + 1, mid + 1, r, pos, val);
        PushUp(u);
        return;
    }

    int Query(int u, int l, int r, int s, int t) {
        if (s > t) return 0;
        if (s <= l && r <= t) {
            return node[u].val;
        }
        int mid = (l + r) / 2;
        if (t <= mid) return Query(u * 2, l, mid, s, t);
        if (s >= mid + 1) return Query(u * 2 + 1, mid + 1, r, s, t);
        return Query(u * 2, l, mid, s, t) + Query(u * 2 + 1, mid + 1, r, s, t);
    }

    void Clear() {
        for (int i = 1; i <= 4 * m; i++) node[i].val = 0;
        return;
    }
} SGT;

void DFSN(int now, int lastR, int lastG) {
    //printf("DFSN %d, r = %d, g = %d\n", now, lastR, lastG);
    if (now > n) {
        cnt = (cnt + 1) % mod;
        sum = std::max(sum, res);
        //printf("colered\n");
        return;
    }
    if (a[now] > lastR) {
        res = (res + SGT.Query(1, 1, m, a[now] + 1, m) * (m - a[now] + 1) % mod) % mod;
        SGT.Add(1, 1, m, a[now], 1);
        DFSN(now + 1, a[now], lastG);
        SGT.Add(1, 1, m, a[now], - 1);
        res = (res - SGT.Query(1, 1, m, a[now] + 1, m) * (m - a[now] + 1) % mod + mod) % mod;
    }
    if (a[now] < lastG) {
        res = (res + SGT.Query(1, 1, m, 1, a[now] - 1) * a[now] % mod) % mod;
        SGT.Add(1, 1, m, a[now], 1);
        DFSN(now + 1, lastR, a[now]);
        SGT.Add(1, 1, m, a[now], - 1);

        res = (res - SGT.Query(1, 1, m, 1, a[now] - 1) * a[now] % mod + mod) % mod;
    }
    return;
}

void DFST(int now) {
    //printf("DFST %d\n", now);
    if (now > n) {
        cnt = 0;
        sum = 0;
        SGT.Clear();
        DFSN(1, 0, m + 1);
        if (cnt > 1) {
            tot++;
            ans = (ans + sum) % mod;
            //for (int i = 1; i <= n; i++) std::cout << a[i] << ' ';
            //std::cout << '\n';
        }
        return;
    }
    for (int i = 1; i <= m; i++) {
        a[now] = i;
        DFST(now + 1);
    }
    return;
}

void mian() {
    cnt = 0;
    res = 0;
    sum = 0;
    tot = 0;
    ans = 0;
    std::cin >> n >> m >> t;
    for (int i = 1; i <= t; i++) std::cin >> a[i];
    DFST(t + 1);
    std::cout << tot << ' ' << ans << '\n';
    return;
}

int main() {
    freopen("color.in", "r", stdin);
    freopen("color.out", "w", stdout);
    std::cin >> C;
    while (C--) mian();
    return 0;
}