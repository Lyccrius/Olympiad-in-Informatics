#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>

typedef std::vector<int> vic;
typedef std::deque<int> diq;

const int maxN = 2e5;
const int maxM = 2e5;
const int sqrN = 447;

int n;
int a[maxN + 10];
int b[maxN + 10];
int bl[maxN + 10];
int br[maxN + 10];
int m;
int l, r;
int ans[maxM + 10];
vic raw;

struct Query {
    int i, l, r;

    bool operator<(const Query &other) const {
        if (b[l] != b[other.l]) return l < other.l;
        return r < other.r;
    }
};

std::deque<Query> query;

int p[maxN + 10];
int pl[maxN + 10];
int pr[maxN + 10];
int bak;
int res;
diq tmp;

int brute(int l, int r) {
    int ret = 0;
    for (int i = l; i <= r; i++) {
        if (p[a[i]]) ret = std::max(ret, i - p[a[i]]);
        else p[a[i]] = i;
    }
    for (int i = l; i <= r; i++) p[a[i]] = 0;
    return ret;
}

void clear() {
    res = 0;
    bak = 0;
    for (int i = 1; i <= n; i++) p[i] = 0;
    for (int i = 1; i <= n; i++) pl[i] = 0;
    for (int i = 1; i <= n; i++) pr[i] = 0;
    return;
}

void addr(int x) {
    if (pl[a[x]]) res = std::max(res, x - pl[a[x]]);
    else pl[a[x]] = x;
    pr[a[x]] = x;
    return;
}

void addl(int x) {
    if (pr[a[x]]) res = std::max(res, pr[a[x]] - x);
    else pr[a[x]] = x, tmp.push_back(a[x]);
    return;
}

void backup() {
    bak = res;
    return;
}

void rollback() {
    res = bak;
    bak = 0;
    for (auto i : tmp) pr[i] = 0;
    tmp.clear();
    return;
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) raw.push_back(a[i]);
    std::sort(raw.begin(), raw.end());
    raw.erase(std::unique(raw.begin(), raw.end()), raw.end());
    for (int i = 1; i <= n; i++) a[i] = std::lower_bound(raw.begin(), raw.end(), a[i]) - raw.begin() + 1;
    for (int i = 1; i <= n; i++) b[i] = (i - 1) / sqrN + 1;
    for (int i = 1; i <= n; i++) br[b[i]] = i;
    for (int i = n; i >= 1; i--) bl[b[i]] = i;
    std::cin >> m;
    for (int i = 1; i <= m; i++) std::cin >> l >> r, query.push_back((Query) {i, l, r});
    std::sort(query.begin(), query.end());
    for (int i = 1; i <= b[n]; i++) {
        clear();
        while (query.size() && query.front().r <= br[i]) {
            ans[query.front().i] = brute(query.front().l, query.front().r);
            query.pop_front();
        }
        l = br[i] + 1;
        r = br[i];
        while (query.size() && query.front().l <= br[i]) {
            Query q = query.front();
            query.pop_front();
            while (r < q.r) addr(++r);
            backup();
            while (l > q.l) addl(--l);
            ans[q.i] = res;
            rollback();
            l = br[i] + 1;
        }
    }
    for (int i = 1; i <= m; i++) std::cout << ans[i] << '\n';
    return 0;
}