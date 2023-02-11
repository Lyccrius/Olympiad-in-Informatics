#include <iostream>
#include <queue>
#include <vector>

typedef long long lxl;

const int maxN = 2e5;

int n, m;
lxl A[maxN + 10];
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
        return x.a < y.a;
    }
};

std::priority_queue<Node, std::vector<Node>, cmp> q;

lxl ans;

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> A[i];
    for (int i = 1; i <= n; i++) LL.node[i].a = A[i];
    for (int i = 1; i <= n; i++) LL.node[i].p = i;
    for (int i = 1; i <= n; i++) LL.node[i].last = i - 1;
    for (int i = 1; i <= n; i++) LL.node[i].next = i + 1;
    LL.node[1].last = n;
    LL.node[n].next = 1;
    if (m > n / 2) {
        std::cout << "Error!";
        return 0;
    }
    for (int i = 1; i <= n; i++) q.push((Node) {A[i], i});
    while (m) {
        int p = q.top().p;
        q.pop();
        if (v[p]) continue;
        ans += A[p];
        A[p] = A[LL.node[p].last] + A[LL.node[p].next] - A[p];
        q.push((Node) {A[p], p});
        LL.Delete(p);
        m--;
    }
    std::cout << ans;
    return 0;
}