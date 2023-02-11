#include <iostream>
#include <queue>
#include <vector>

typedef long long lxl;

const int maxN = 5e5;
const int inf = 1e9;

int n, k;
lxl s[maxN + 10];
lxl a[maxN + 10];
int v[maxN + 10];

struct LinkedList {
    struct Node {
        lxl a;
        int p;
        int last;
        int next;
    } node[maxN + 10];

    void Delete(int p) {
        v[node[p].last] = true;
        v[node[p].next] = true;
        node[p].last = node[node[p].last].last;
        node[p].next = node[node[p].next].next;
        node[node[p].last].next = p;
        node[node[p].next].last = p;
        return;
    }
} LL;

struct Node {
    lxl a;
    int p;
};

struct cmp {
    inline bool operator() (const Node &x, const Node &y) {
        return x.a > y.a;
    }
};

std::priority_queue<Node, std::vector<Node>, cmp> q;

lxl ans;

int main() {
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) std::cin >> s[i];
    for (int i = 1; i <= n; i++) a[i] = s[i + 1] - s[i]; a[0] = a[n] = inf; n--;
    for (int i = 1; i <= n; i++) LL.node[i].a = a[i];
    for (int i = 1; i <= n; i++) LL.node[i].p = i;
    for (int i = 1; i <= n; i++) LL.node[i].last = i - 1;
    for (int i = 1; i <= n; i++) LL.node[i].next = i + 1;
    //LL.node[1].last = n;
    //LL.node[n].next = 1;
    for (int i = 1; i <= n; i++) q.push((Node) {a[i], i});
    while (k) {
        int p = q.top().p;
        q.pop();
        if (v[p]) continue;
        if (a[p] <= 0) break;
        ans += a[p];
        a[p] = a[LL.node[p].last] + a[LL.node[p].next] - a[p];
        q.push((Node) {a[p], p});
        LL.Delete(p);
        k--;
    }
    std::cout << ans;
    return 0;
}