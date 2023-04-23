#include <iostream>
#include <algorithm>
#include <queue>

typedef long long lxl;

const int maxN = 3e5;
const int inf = 1e9 + 1;

int n;
int x;
int s[maxN + 10];
struct Problem {
    int i;
    int t, s, p;
    int r;

    bool operator<(const Problem &other) const {
        return r < other.r;
    }
} p[maxN + 10];
lxl T;

lxl res[maxN + 10];

bool cmpByP(const Problem& a, const Problem& b) {
    return a.p < b.p;
}

bool cmpByT(const Problem& a, const Problem& b) {
    return a.t < b.t;
}

void calc() {
    lxl now = 0;
    std::priority_queue<Problem> q;
    for (int i = 1; i <= n; i++) {
        int gap = p[i].t - now;
        while (gap > 0 && q.size()) {
            if (gap >= q.top().s) {
                gap -= q.top().s;
                now += q.top().s;
                res[q.top().i] = now;
                q.pop();
            } else {
                Problem t = q.top();
                q.pop();
                t.s -= gap;
                q.push(t);
                gap = 0;
            }
        }
        now = p[i].t;
        q.push(p[i]);
        if (p[i].t == p[i + 1].t) continue;
    }
    while (q.size()) {
        now += q.top().s;
        res[q.top().i] = now;
        q.pop();
    }
    return;
}

bool check(int mid) {
    for (int i = 1; i <= n; i++) if (p[i].r <= mid) p[i].r--;
    p[x].r = mid;
    calc();
    for (int i = 1; i <= n; i++) if (p[i].r <= mid) p[i].r++;
    return res[p[x].i] < T;
}

signed main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> p[i].t >> p[i].s >> p[i].p;
    std::cin >> T;
    for (int i = 1; i <= n; i++) p[i].i = i;
    std::sort(p + 1, p + n + 1, cmpByP);
    for (int i = 1; i <= n; i++) p[i].r = i;
    std::sort(p + 1, p + n + 1, cmpByT);
    for (int i = 1; i <= n; i++) if (p[i].p == -1) x = i;
    int l = 1;
    int r = n;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (check(mid)) r = mid - 1;
        else l = mid;
    }
    while (l > 1) {
        check(l - 1);
        if (res[p[x].i] == T) l--;
        else break;
    }
    while (r < n) {
        check(r + 1);
        if (res[p[x].i] == T) r++;
        else break;
    }
    check(l);
    std::sort(p + 1, p + n + 1, cmpByP);
    int ans;
    for (int i = l; i <= r; i++) {
        if (p[i + 1].p - p[i].p > 1) {
            ans = p[i].p + 1;
            if (ans >= 1) break;
        }
    }
    std::cout << ans << '\n';
    for (int i = 1; i <= n; i++) std::cout << res[i] << ' ';
    return 0;
}