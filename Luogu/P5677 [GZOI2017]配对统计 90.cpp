#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>

typedef long long lxl;
typedef std::vector<int> vic;

const int maxN = 3e5;
const int maxM = 3e5;
const int sqrtN = 528;

int n, m;
int a[maxN + 10];
int b[maxN + 10];
int c[maxN + 10];
int l, r;
vic other[maxN + 10];
int res;
lxl ans;

struct Node {
    int a;
    int i;

    bool operator<(const Node &other) const {
        return a < other.a;
    }
};

struct Query {
    int i;
    int l;
    int r;

    bool operator<(const Query &other) const {
        if (b[l] != b[other.l]) return b[l] < b[other.l];
        return r < other.r;
    }
};

std::deque<Node> nodes;
std::deque<Query> querys;

struct CapmainMo {
    void Add(int pos, int l, int r) {
        res += c[pos];
        for (auto i : other[pos]) {
            c[i]++;
            if (l <= i && i <= r) {
                res++;
            }
        }
        return;
    }

    void Del(int pos, int l, int r) {
        for (auto i : other[pos]) {
            c[i]--;
            if (l <= i && i <= r) {
                res--;
            }
        }
        res -= c[pos];
        return;
    }
} CMO;

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) nodes.push_back((Node) {a[i], i});
    std::sort(nodes.begin(), nodes.end());
    for (int i = 0; i < nodes.size(); i++) {
        if (i == 0 && i == nodes.size() - 1) continue;
        if (i == 0) {
            other[nodes[i].i].push_back(nodes[i + 1].i);
            continue;
        }
        if (i == nodes.size() - 1) {
            other[nodes[i].i].push_back(nodes[i - 1].i);
            continue;
        }
        int dl = nodes[i].a - nodes[i - 1].a;
        int dr = nodes[i + 1].a - nodes[i].a;
        if (dl <= dr) {
            other[nodes[i].i].push_back(nodes[i - 1].i);
        }
        if (dl >= dr) {
            other[nodes[i].i].push_back(nodes[i + 1].i);
        }
    }
    for (int i = 1; i <= n; i++) b[i] = (i - 1) / sqrtN + 1;
    for (int i = 1; i <= m; i++) std::cin >> l >> r, querys.push_back((Query) {i, l, r});
    std::sort(querys.begin(), querys.end());
    l = 1;
    r = 0;
    for (auto query : querys) {
        while (l > query.l) l--, CMO.Add(l, l, r);
        while (r < query.r) r++, CMO.Add(r, l, r);
        while (r > query.r) CMO.Del(r, l, r), r--;
        while (l < query.l) CMO.Del(l, l, r), l++;
        ans += 1ll * res * query.i;
    }
    std::cout << ans;
    return 0;
}