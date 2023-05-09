#include <iostream>
#include <algorithm>
#include <deque>

typedef std::deque<int> diq;

const int maxN = 1500;
const int maxM = 3e5;
const int maxW = 1e4;
const int inf = 1e9 + 10;

int n, m;
int s1, t1, s2, t2;
int u, v, w;

struct Graph {
    struct Vertex {
        int head;
        int dis;
        int vis;
        int deg;
        int res;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        int weight;
    } edge[2 * maxM + 10];

    int ecnt;

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        return;
    }

    void SPFA(int s) {
        for (int i = 1; i <= n; i++) vertex[i].dis = inf;
        for (int i = 1; i <= n; i++) vertex[i].vis = false;
        diq q;
        q.push_back(s);
        vertex[s].dis = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            if (vertex[u].vis) continue;
            vertex[u].vis = true;
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                int w = edge[e].weight;
                if (vertex[v].dis > vertex[u].dis + w) {
                    vertex[v].dis = vertex[u].dis + w;
                    vertex[v].vis = false;
                    q.push_back(v);
                }
            }
        }
        /*
        for (int i = 1; i <= n; i++) {
            printf("dis[%d] = %d\n", i, vertex[i].dis);
        }
        */
        return;
    }
} E, W;

int main() {
    std::cin >> n >> m;
    std::cin >> s1 >> t1 >> s2 >> t2;
    for (int i = 1; i <= m; i++) {
        std::cin >> u >> v >> w;
        E.addEdge(u, v, w);
        E.addEdge(v, u, w);
        W.addEdge(u, v, w);
        W.addEdge(v, u, w);
    }
    E.SPFA(s1);
    W.SPFA(s2);
    diq q;
    for (int u = 1; u <= n; u++) {
        E.vertex[u].vis = false;
    }
    q.push_back(t1);
    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        if (E.vertex[u].vis) continue;
        E.vertex[u].vis = true;
        for (int e = E.vertex[u].head; e; e = E.edge[e].next) {
            int v = E.edge[e].head;
            int w = E.edge[e].weight;
            if (E.vertex[u].dis == E.vertex[v].dis + w) {
                E.vertex[u].deg++;
                q.push_back(v);
            }
        }
    }
    for (int u = 1; u <= n; u++) {
        W.vertex[u].vis = false;
    }
    q.push_back(t2);
    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        if (W.vertex[u].vis) continue;
        W.vertex[u].vis = true;
        for (int e = W.vertex[u].head; e; e = W.edge[e].next) {
            int v = W.edge[e].head;
            int w = W.edge[e].weight;
            if (W.vertex[u].dis == W.vertex[v].dis + w) {
                W.vertex[u].deg++;
                q.push_back(v);
            }
        }
    }
    /*
    printf("\n");
    for (int u = 1; u <= n; u++) {
        if (E.vertex[u].vis) {
            printf("%d on deg E\n", u);
        }
    }
    printf("\n");
    for (int u = 1; u <= n; u++) {
        if (W.vertex[u].vis) {
            printf("%d on deg W\n", u);
        }
    }
    printf("\n");
    */
    for (int u = 1; u <= n; u++) {
        //printf("deg[%d] = %d\n", u, E.vertex[u].deg);
        if (E.vertex[u].deg == 0) {
            q.push_back(u);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        //printf("%d: %d\n", u, E.vertex[u].res);
        for (int e = E.vertex[u].head; e; e = E.edge[e].next) {
            int v = E.edge[e].head;
            int w = E.edge[e].weight;
            //printf("%d to %d, %d\n", u, v, w);
            if (E.vertex[v].dis == E.vertex[u].dis + w) {
                if (W.vertex[v].vis && W.vertex[u].vis) {
                    if (W.vertex[v].dis == W.vertex[u].dis + w || W.vertex[u].dis == W.vertex[v].dis + w) {
                        E.vertex[v].res = std::max(E.vertex[v].res, E.vertex[u].res + w);
                    }
                }
                E.vertex[v].res = std::max(E.vertex[v].res, E.vertex[u].res);
                E.vertex[v].deg--;
                if (E.vertex[v].deg == 0) {
                    q.push_back(v);
                }
            }
        }
    }
    std::cout << E.vertex[t1].res << '\n';
    return 0;
}