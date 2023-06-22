#include <iostream>
#include <algorithm>
#include <cstring>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef char chr;
typedef unsigned long long ull;

const int maxN = 1e5;
const ull base = 47;

int t;

namespace str {
    int n;
    chr s[maxN + 10];
    ull p[maxN + 10];
    ull h[maxN + 10];
    int sa[maxN + 10];
    int rk[maxN + 10];
    int ht[maxN + 10];

    void read() {
        std::cin >> (s + 1);
        n = strlen(s + 1);
        return;
    }

    void calc() {
        p[0] = 1;
        for (int i = 1; s[i]; i++) p[i] = p[i - 1] * base;
        for (int i = 1; s[i]; i++) h[i] = h[i - 1] * base + s[i] - 'a' + 1;
        return;
    }

    ull hash(int l, int r) {
        return h[r] - h[l - 1] * p[r - l + 1];
    }

    int lcp(int i, int j) {
        int l = 0;
        int r = std::min(n - i + 1, n - j + 1);
        while (l < r) {
            int mid = (l + r + 1) / 2;
            if (hash(i, i + mid - 1) == hash(j, j + mid - 1)) l = mid;
            else r = mid - 1;
        }
        return l;
    }

    bool cmp(int i, int j) {
        int k = lcp(i, j);
        return s[i + k] < s[j + k];
    }
    
    void sort() {
        for (int i = 1; i <= n; i++) sa[i] = i;
        std::stable_sort(sa + 1, sa + n + 1, cmp);
        for (int i = 1; i <= n; i++) rk[sa[i]] = i;
        for (int i = 1; i <= n; i++) {
            if (rk[i] == 1) {
                ht[rk[i]] = 0;
                continue;
            }
            ht[rk[i]] = std::max(ht[rk[i - 1]] - 1, 0);
            while (s[i + ht[rk[i]]] == s[sa[rk[i] - 1] + ht[rk[i]]]) ht[rk[i]]++;
        }
        return;
    }
}

struct SegmentTree {
    struct Node {
        ull pow;
        ull cnt;
        ull tag;
        int del;
    } node[4 * maxN + 10], e;

    void makeTag(int u, int l, int r, int val) {
        node[u].pow += val * ((r - l + 1) * val + 2 * node[u].cnt);
        node[u].cnt += val * (r - l + 1);
        node[u].tag += val;
        return;
    }

    void makeDel(int u) {
        node[u].pow = 0;
        node[u].cnt = 0;
        node[u].tag = 0;
        node[u].del = 1;
        return;
    }

    void pushDown(int u, int l, int r) {
        if (node[u].del) {
            makeDel(2 * u);
            makeDel(2 * u + 1);
            node[u].del = false;
        }
        int mid = (l + r) / 2;
        if (node[u].tag) {
            makeTag(2 * u, l, mid, node[u].tag);
            makeTag(2 * u + 1, mid + 1, r, node[u].tag);
            node[u].tag = 0;
        }
        return;
    }

    void pushUp(int u) {
        node[u].pow = node[2 * u].pow + node[2 * u + 1].pow;
        node[u].cnt = node[2 * u].cnt + node[2 * u + 1].cnt;
        return;
    }

    ull ask(int u, int l, int r, int s, int t) {
        if (s <= l && r <= t) {
            ull ret =  node[u].pow;
            makeDel(u);
            return ret;
        }
        pushDown(u, l, r);
        int mid = (l + r) / 2;
        ull ret = 0;
        if (s <= mid) ret += ask(2 * u, l, mid, s, t);
        if (t >= mid + 1) ret += ask(2 * u + 1, mid + 1, r, s, t);
        pushUp(u);
        return ret;
    }

    void add(int u, int l, int r, int s, int t) {
        if (s <= l && r <= t) {
            makeTag(u, l, r, 1);
            return;
        }
        pushDown(u, l, r);
        int mid = (l + r) / 2;
        if (s <= mid) add(2 * u, l, mid, s, t);
        if (t >= mid + 1) add(2 * u + 1, mid + 1, r, s, t);
        pushUp(u);
        return;
    }
} sgt;

ull ans;

void mian() {
    str::read();
    str::calc();
    str::sort();
    ans = 0;
    for (int i = 1, j = 0; i <= str::n; j = str::n - str::sa[i] + 1, i++) {
        if (str::ht[i] < j) {
            ans += sgt.ask(1, 1, str::n, str::ht[i] + 1, j);
        }
        sgt.add(1, 1, str::n, 1, str::n - str::sa[i] + 1);
    }
    ans += sgt.ask(1, 1, str::n, 1, str::n - str::sa[str::n] + 1);
    sgt.ask(1, 1, str::n, 1, str::n);
    std::cout << ans << '\n';
    return;
}

int main() {
    promote();
    std::cin >> t;
    while (t--) mian();
    return 0;
}