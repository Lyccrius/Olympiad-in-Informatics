#include <iostream>

typedef char chr;

const int maxN = 1e5;
const int maxM = 1e5;

int n, m;
chr s[maxN + 10];
int l, r;
int mid;
int cnt[30];
int odd;
int cur;
int len;
int pos;

bool check() {
    len = (r - l + 1);
    if (len & 1) {
        if (odd == 1) return true;
        else return false;
    } else {
        if (odd) return false;
        else return true;
    }
}

struct SegmentTree {
    struct Node {
        int val;
        int tag;
    } node[maxN * 4 + 10];

    void MakeTag(int u, int l, int r, int tag) {
        node[u].val = tag - 1;
        node[u].tag = tag;
        return;
    }

    void PushDown(int u, int l, int r) {
        if (!node[u].tag) return;
        int mid = (l + r) / 2;
        MakeTag(u * 2, l, mid, node[u].tag);
        MakeTag(u * 2 + 1, mid + 1, r, node[u].tag);
        node[u].tag = 0;
        return;
    }

    void PushUp(int u) {
        node[u].val = node[u * 2].val + node[u * 2 + 1].val;
        return;
    }

    void Modify(int u, int l, int r, int s, int t, int val) {
        if (s <= l && r <= t) {
            MakeTag(u, l, r, val + 1);
            return;
        }
        PushDown(u, l, r);
        int mid = (l + r) / 2;
        if (s <= mid) Modify(u * 2, l, mid, s, t, val);
        if (t >= mid + 1) Modify(u * 2 + 1, mid + 1, r, s, t, val);
        PushUp(u);
        return;
    }

    int Query(int u, int l, int r, int s, int t) {
        if (s <= l && r <= t) return node[u].val;
        PushDown(u, l, r);
        int mid = (l + r) / 2;
        if (t <= mid) return Query(u * 2, l, mid, s, t);
        if (s >= mid + 1) return Query(u * 2 + 1, mid + 1, r, s, t);
        return Query(u * 2, l, mid, s, t) + Query(u * 2 + 1, mid + 1, r, s, t);
    }
} SGT[30];

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    std::cin >> n >> m;
    std::cin >> (s + 1);
    for (int i = 1; i <= n; i++) SGT[s[i] - 'a'].Modify(1, 1, n, i, i, 1);
    for (int i = 1; i <= m; i++) {
        std::cin >> l >> r; mid = (l + r) / 2;
        for (int j = 0; j < 26; j++) cnt[j] = SGT[j].Query(1, 1, n, l, r); odd = 0; cur = 26;
        for (int j = 0; j < 26; j++) if (cnt[j] & 1) odd++, cur = j;
        if (!check()) continue;
        for (int j = 0; j < 26; j++) SGT[j].Modify(1, 1, n, l, r, 0);
        SGT[cur].Modify(1, 1, n, mid, mid, 1), cnt[cur]--;
        for (int j = 0; j < 26; j++) while (cnt[j]) {
            SGT[j].Modify(1, 1, n, l, l, 1);
            SGT[j].Modify(1, 1, n, r, r, 1);
            cnt[j]--;
            cnt[j]--;
            l++;
            r--;
        }
    }
    for (int i = 1; i <= n; i++) for (int j = 0; j < 26; j++) if (SGT[j].Query(1, 1, n, i, i)) {s[i] = 'a' + j; break;}
    std::cout << (s + 1);
    return 0;
}