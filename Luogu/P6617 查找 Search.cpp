#include <iostream>
#include <algorithm>
#include <set>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef std::set<int>::iterator sit;

const int maxN = 5e5;
const int maxM = 5e5;
const int maxW = 5e5;

int n, m, w;
int a[maxN + 10];
int op;
int pos, val;
int l, r;
int cnt;

std::set<int> appear[maxW + 10];
int match[maxN + 10];

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
            node[u].val = match[l];
            return;
        }
        int mid = (l + r) / 2;
        Build(u * 2, l, mid);
        Build(u * 2 + 1, mid + 1, r);
        PushUp(u);
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
        int ret = 0;
        int mid = (l + r) / 2;
        if (s <= mid) ret = std::max(ret, Query(u * 2, l, mid, s, t));
        if (t >= mid + 1) ret = std::max(ret, Query(u * 2 + 1, mid + 1, r, s, t));
        return ret;
    }
} SGT;

int last[maxW + 10];

int main() {
    promote();
    std::cin >> n >> m >> w;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) {
        if (appear[w - a[i]].size()) {
            sit it = appear[w - a[i]].end(); it--;
            match[i] = *it;
        }
        appear[a[i]].insert(i);
    }
    SGT.Build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        std::cin >> op;
        if (op == 1) {
            std::cin >> pos >> val;
            sit it;
            int last;
            if (appear[a[pos]].empty() || pos == *appear[a[pos]].begin()) {
                last = 0;
            } else {
                it = appear[a[pos]].lower_bound(pos); it--;
                last = *it;
            }
            it = appear[w - a[pos]].lower_bound(pos);
            while (it != appear[w - a[pos]].end() && match[*it] == pos) {
                match[*it] = last;
                SGT.Modify(1, 1, n, *it, last);
                it++;
            }
            appear[a[pos]].erase(pos);
            a[pos] = val;
            appear[a[pos]].insert(pos);
            it = appear[w - a[pos]].lower_bound(pos);
            while (it != appear[w - a[pos]].end() && match[*it] < pos) {
                match[*it] = pos;
                SGT.Modify(1, 1, n, *it, pos);
                it++;
            }
            if (appear[w - a[pos]].empty() || pos < *appear[w - a[pos]].begin()) {
                match[pos] = 0;
            } else {
                it = appear[w - a[pos]].lower_bound(pos); it--;
                match[pos] = *it;
            }
            SGT.Modify(1, 1, n, pos, match[pos]);
        } else if (op == 2) {
            std::cin >> l >> r;
            l ^= cnt;
            r ^= cnt;
            int res = SGT.Query(1, 1, n, l, r);
            if (res >= l) {
                std::cout << "Yes" << '\n';
                cnt++;
            } else {
                std::cout << "No" << '\n';
            }
        }
    }
    return 0;
}