#include <cstdio>
#include <vector>
#include <algorithm>

const int maxN = 3e5;
const int maxM = 3e5;
const int maxK = 3e5;

int n, m;
int o[maxM + 10];
int p[maxN + 10];
int k;
int l[maxK + 10], r[maxK + 10], a[maxK + 10];

struct Country {
    int id;
    long long p;
};
std::vector<Country> country;
std::vector<int> v[maxN];

struct BinaryIndexedTree {
    struct Node {
        long long val;
    } node[maxM];

    int lowbit(int x) {
        return x & -x;
    }

    void Add(int pos, int val) {
        while (pos <= m) {
            node[pos].val += val;
            pos += lowbit(pos);
        }
        return;
    }

    long long Ask(int pos) {
        long long res = 0;
        while (pos > 0) {
            res += node[pos].val;
            pos -= lowbit(pos);
        }
        return res;
    }
} BIT;

int res[maxN];

void solve(int L, int R, std::vector<Country> q) {
    int mid = (L + R) >> 1;
    std::vector<Country> q1;
    std::vector<Country> q2;
    for (int i = L; i <= mid; i++) {
        BIT.Add(l[i], a[i]);
        BIT.Add(r[i] + 1, -a[i]);
        if (l[i] > r[i]) BIT.Add(1, a[i]);
    }
    for (int i = 0; i < q.size(); i++) {
        long long c = 0;
        for (int j = 0; j < v[q[i].id].size(); j++) {
            c += BIT.Ask(v[q[i].id][j]);
            if (c >= q[i].p) break;
        }
        if (c >= q[i].p) q1.push_back(q[i]);
        else q[i].p -= c, q2.push_back(q[i]);
    }
    for (int i = L; i <= mid; i++) {
        BIT.Add(l[i], -a[i]);
        BIT.Add(r[i] + 1, a[i]);
        if (l[i] > r[i]) BIT.Add(1, -a[i]);
    }
    if (L == R) {
        for (int i = 0; i < q1.size(); i++) res[q1[i].id] = L;
        for (int i = 0; i < q2.size(); i++) res[q2[i].id] = -1;
        return;
    }
    solve(L, mid, q1);
    solve(mid + 1, R, q2);
    return;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) scanf("%d", &o[i]), v[o[i]].push_back(i);
    for (int i = 1; i <= n; i++) scanf("%d", &p[i]), country.push_back((Country){i, p[i]});
    scanf("%d", &k);
    for (int i = 1; i <= k; i++) scanf("%d%d%d", &l[i], &r[i], &a[i]);
    solve(1, k, country);
    for (int i = 1; i <= n; i++) if (res[i] > 0) printf("%d\n", res[i]); else printf("NIE\n");
    return 0;
}