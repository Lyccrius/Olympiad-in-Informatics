#include <iostream>
#include <stack>

typedef long long lxl;

const int maxN = 1e5;
const int maxM = 2e5;

int n, m;
int v, u;

lxl ans;
//int qwq = 1;

namespace graph {
    struct Vertex {
        int head;
        int dfn;
        int low;
        int size;
    } vertex[maxN * 2 + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxM * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    int dfn;

    std::stack<int> s;

    int tot;

    void init() {
        while (!s.empty()) s.pop();
        tot = 0;
        return;
    }

    namespace blockForest {
        Vertex vertex[maxN * 2 + 10];
        int vcnt;

        Edge edge[maxM * 2 + 10];
        int ecnt;

        void addEdge(int tail, int head) {
            blockForest::ecnt++;
            blockForest::edge[ecnt].head = head;
            blockForest::edge[ecnt].next = vertex[tail].head;
            blockForest::vertex[tail].head = ecnt;
            return;
        }

        void DFS(int u, int from) {
            //for (int i = 1; i <= qwq; i++) printf("-");
            //printf("DFS(%d, %d)\n", u, from);
            //qwq++;
            //if (u <= n) blockForest::vertex[u].size = 1;
            blockForest::vertex[u].size = (u <= n);
            lxl cnt = 0;
            for (int e = blockForest::vertex[u].head; e; e = blockForest::edge[e].next) {
                int v = blockForest::edge[e].head;
                if (v == from) continue;
                DFS(v, u);
                cnt += 1ll * blockForest::vertex[u].size * blockForest::vertex[v].size;
                //printf("size[%d] += size[%d] (%d) = %d\n", u, v, vertex[v].size, vertex[u].size);
                //printf("cnt = %d\n", cnt);
                blockForest::vertex[u].size += blockForest::vertex[v].size;
                //for (int i = 1; i <= qwq; i++) printf("-");
                //printf("size[%d] += size[%d] (%d) = %d\n", u, v, vertex[v].size, vertex[u].size);
            }
            cnt += 1ll * blockForest::vertex[u].size * (tot - blockForest::vertex[u].size);
            cnt *= 2;
            ans += 1ll * graph::vertex[u].size * cnt;
            //printf("osize[%d] = %d\n", u, graph::vertex[u].size);
            //for (int i = 1; i <= qwq; i++) printf("-");
            //printf("ans = %lld\n", ans);
            //printf("graph::vertex[%d] = %d\n", u, graph::vertex[u].size);
            //qwq--;
            return;
        }
    }

    void addVBCC(int u) {
        blockForest::vcnt++;
        //vertex[blockForest::vcnt].size = 1;
        int v;
        do {
            v = s.top();
            s.pop();
            vertex[blockForest::vcnt].size++;
            blockForest::addEdge(v, blockForest::vcnt);
            blockForest::addEdge(blockForest::vcnt, v);
            //printf("add %d, %d\n", v, blockForest::vcnt);
        } while (v != u);
        return;
    }

    void Tarjan(int u) {
        vertex[u].size = -1;
        tot++;
        dfn++;
        vertex[u].dfn = dfn;
        vertex[u].low = dfn;
        s.push(u);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (vertex[v].dfn) {
                vertex[u].low = std::min(vertex[u].low, vertex[v].dfn);
            } else {
                Tarjan(v);
                vertex[u].low = std::min(vertex[u].low, vertex[v].low);
                if (vertex[u].dfn <= vertex[v].low) {
                    s.push(u);
                    addVBCC(v);
                }
            }
        }
        return;
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> v >> u;
        graph::addEdge(v, u);
        graph::addEdge(u, v);
    }
    graph::blockForest::vcnt = n;
    for (int i = 1; i <= n; i++) {
        if (!graph::vertex[i].dfn) {
            graph::init();
            graph::Tarjan(i);
            graph::blockForest::DFS(i, 0);
        }
    }
    std::cout << ans;
    return 0;
}