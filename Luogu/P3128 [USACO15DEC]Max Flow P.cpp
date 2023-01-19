#include <iostream>
#include <algorithm>
#include <cmath>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 5e4;
const int maxK = 1e5;
const int logN = 17;

int N, K;
int x, y;
int s[maxK + 10], t[maxK + 10];
int res;
int ans;

namespace tree {
    struct Vertex {
        int head;
        int val;
        int dep;
        int fa[logN + 5];
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxN * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void DFS(int u, int from) {
        //printf("DFSing %d\n", u);
        for (int p = 1; p <= logN; p++) vertex[u].fa[p] = vertex[vertex[u].fa[p - 1]].fa[p - 1];
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            vertex[v].fa[0] = u;
            vertex[v].dep = vertex[u].dep + 1;
            DFS(v, u);
            vertex[u].val += vertex[v].val;
        }
        ans = std::max(ans, vertex[u].val);
        //printf("val[%d] = %d\n", u, vertex[u].val);
        return;
    }

    int LCA(int u, int v) {
        if (vertex[u].dep < vertex[v].dep) std::swap(u, v);
        while (vertex[u].dep > vertex[v].dep) {
            //printf("u = %d at %d, v = %d at %d\n", u, vertex[u].dep, v, vertex[v].dep);
            //printf("%d\n", (int)std::log2(vertex[u].dep - vertex[v].dep));
            u = vertex[u].fa[(int)std::log2(vertex[u].dep - vertex[v].dep)];
            //printf("U = %d\n", u);
        }
        if (u == v) return u;
        for (int p = logN; p >= 0; p--) {
            if (vertex[u].fa[p] != vertex[v].fa[p]) {
                u = vertex[u].fa[p];
                v = vertex[v].fa[p];
                //printf("%d, %d\n", u, v);
            }
        }
        return vertex[u].fa[0];
    }

    void mian() {
        DFS(1, 0);
        
        /*
         (int i = 1; i <= N; i++) {
            for (int p = 0; p <= logN; p++) printf("%d ", vertex[i].fa[p]);
            printf("\n");
        }
        */
        for (int i = 1; i <= K; i++) {
            vertex[s[i]].val++, vertex[t[i]].val++, vertex[LCA(s[i], t[i])].val--, vertex[vertex[LCA(s[i], t[i])].fa[0]].val--;
            //printf("%d++\n", s[i]);
            //printf("%d++\n", t[i]);
            //printf("%d--\n", LCA(s[i], t[i]));
            //printf("%d--\n", vertex[LCA(s[i], t[i])].fa[0]);
        }
        DFS(1, 0);
    }
}

int main() {
    promote();
    std::cin >> N >> K;
    for (int i = 1; i < N; i++) std::cin >> x >> y, tree::addEdge(x, y), tree::addEdge(y, x);
    for (int i = 1; i <= K; i++) std::cin >> s[i] >> t[i];
    tree::mian();
    std::cout << ans << '\n';
    return 0;
}