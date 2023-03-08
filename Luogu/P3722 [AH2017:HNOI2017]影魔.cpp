#include <iostream>
#include <algorithm>
#include <deque>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;
typedef std::deque<int> dic;

const int maxN = 2e5;
const int maxM = 2e5;
const int maxP = 1e3;

int n, m, p1, p2;
int k[maxN + 10];
int a, b;
int pre[maxN + 10];
int suf[maxN + 10];

struct Event {
    int x;
    int l;
    int r;
    int d;

    bool operator<(const Event &other) const {
        return x < other.x;
    }
};

struct Query {
    int i;
    int x;
    int l;
    int r;
    int d;

    bool operator<(const Query &other) const {
        return x < other.x;
    }
};

std::deque<Event> events;
std::deque<Query> querys;

lxl ans[maxM + 10];

struct SegmentTree {
    struct Node {
        lxl val;
        lxl tag;
    } node[maxN * 4 + 10];

    void MakeTag(int u, int l, int r, lxl val) {
        node[u].val += val * (r - l + 1);
        node[u].tag += val;
        return;
    }

    void PushUp(int u) {
        node[u].val = node[u * 2].val + node[u * 2 + 1].val;
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

    void Modify(int u, int l, int r, int s, int t, lxl val) {
        if (s <= l && r <= t) {
            MakeTag(u, l, r, val);
            return;
        }
        PushDown(u, l, r);
        int mid = (l + r) / 2;
        if (s <= mid) Modify(u * 2, l, mid, s, t, val);
        if (t >= mid + 1) Modify(u * 2 + 1, mid + 1, r, s, t, val);
        PushUp(u);
        return;
    }

    lxl Query(int u, int l, int r, int s, int t) {
        if (s <= l && r <= t) return node[u].val;
        PushDown(u, l, r);
        int mid = (l + r) / 2;
        if (t <= mid) return Query(u * 2, l, mid, s, t);
        if (s >= mid + 1) return Query(u * 2 + 1, mid + 1, r, s, t);
        return Query(u * 2, l, mid, s, t) + Query(u * 2 + 1, mid + 1, r, s, t);
    }
} SGT;

int main() {
    promote();
    std::cin >> n >> m >> p1 >> p2;
    for (int i = 1; i <= n; i++) std::cin >> k[i];
    dic s;
    for (int i = 1; i <= n; i++) {
        while (s.size() && k[s.back()] < k[i]) {
            suf[s.back()] = i;
            s.pop_back();
        }
        s.push_back(i);
    }
    while (s.size()) {
        suf[s.back()] = n + 1;
        s.pop_back();
    }
    for (int i = n; i >= 1; i--) {
        while (s.size() && k[s.back()] < k[i]) {
            pre[s.back()] = i;
            s.pop_back();
        }
        s.push_back(i);
    }
    while (s.size()) {
        pre[s.back()] = 0;
        s.pop_back();
    }
    for (int i = 1; i <= n; i++) {
        if (pre[i] != 0 && suf[i] != n + 1) events.push_back((Event) {pre[i], suf[i], suf[i], p1});
        if (pre[i] != 0 && suf[i] != i + 1) events.push_back((Event) {pre[i], i + 1, suf[i] - 1, p2});
        if (pre[i] != i - 1 && suf[i] != n + 1) events.push_back((Event) {suf[i], pre[i] + 1, i - 1, p2});
    }
    for (int i = 1; i <= m; i++) {
        std::cin >> a >> b;
        ans[i] += 1ll * (b - a) * p1;
        querys.push_back((Query) {i, a - 1, a, b, - 1});
        querys.push_back((Query) {i, b, a, b, 1});
    }
    std::sort(events.begin(), events.end());
    std::sort(querys.begin(), querys.end());
    for (auto query : querys) {
        while (events.size() && events.front().x <= query.x) {
            SGT.Modify(1, 1, n, events.front().l, events.front().r, events.front().d);
            events.pop_front();
        }
        ans[query.i] += 1ll * query.d * SGT.Query(1, 1, n, query.l, query.r);
    }
    for (int i = 1; i <= m; i++) std::cout << ans[i] << '\n';
    return 0;
}