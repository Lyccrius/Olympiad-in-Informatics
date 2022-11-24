#include <cstdio>
#include <vector>
#include <cstring>

const int maxN = 4e5 + 10;
const int maxM = 2e5 + 10;
const int maxK = 2e6 + 10;

int n, m;
int x, y;
int k;
int cnt;
int hit[maxK];

namespace War {
    struct Vertex {
        int bel;
        int head;
        bool hited;
    } vertex[maxN];
    struct Edge {
        int head;
        int next;
    } edge[maxM << 1];
    int ecnt;
    int tot;

    void AddEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void Hit(int x) {
        if (vertex[x].hited) return;
        vertex[x].hited = true;
        cnt++;
        return;
    }

    int Find(int x) {
        if (vertex[x].bel == x) return x;
        return vertex[x].bel = Find(vertex[x].bel);
    }

    void Union(int x, int y) {
        x = Find(x);
        y = Find(y);
        if (x == y) return;
        tot--;
        vertex[x].bel = y;
        return;
    }

    void Init() {
        tot = n - cnt;
        for (int u = 0; u < n; u++) vertex[u].bel = u;
        for (int u = 0; u < n; u++) {
            if (!vertex[u].hited) for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                if (!vertex[v].hited) Union(u, v);
            }
        }
        return;
    }

    void Restore(int u) {
        if (!vertex[u].hited) return;
        tot++;
        vertex[u].hited = false;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (!vertex[v].hited) Union(u, v);
        }
        return;
    }

    int Query() {
        return tot;
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        War::AddEdge(x, y);
        War::AddEdge(y, x);
    }
    scanf("%d", &k);
    for (int i = 1; i <= k; i++) {
        scanf("%d", &hit[i]);
        War::Hit(hit[i]);
    }
    War::Init();
    std::vector<int> ans;
    ans.push_back(War::tot);
    for (int i = k; i >= 1; i--) {
        War::Restore(hit[i]);
        ans.push_back(War::Query());
    }
    while (!ans.empty()) {
        printf("%d\n", ans.back());
        ans.pop_back();
    }
    return 0;
}