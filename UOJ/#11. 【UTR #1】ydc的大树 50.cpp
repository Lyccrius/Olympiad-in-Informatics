#include <iostream>
#include <bitset>
#include <vector>
#include <cstring>

const int maxN = 1e3;
const int maxM = 1e3;

typedef std::bitset<maxN + 10> bit;
typedef std::vector<int> vic;

int n, m;
int b[maxM + 10];
int u, v, l;

namespace graph {
    struct Vertex {
        int head;
        int type;
        int dis;
        vic fri;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        int weight;
    } edge[2 * maxN + 10];

    int ecnt;

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        return;
    }

    int dis[maxN + 10][maxN + 10];
    bit pas[maxN + 10][maxN + 10];
    vic vis;
    
    void DFS(int u, int from) {
        vis.push_back(u);
        //printf("DFS %d from %d\n", u, from);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == from) continue;
            for (auto x : vis) {
                dis[x][v] = dis[x][u] + w;
                pas[x][v] = pas[x][u];
                pas[x][v][v] = true;
                dis[v][x] = dis[x][u] + w;
                pas[v][x] = pas[x][u];
                pas[v][x][v] = true;
            }
            DFS(v, u);
        }
        return;
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> b[i];
        graph::vertex[b[i]].type = true;
    }
    for (int i = 1; i < n; i++) {
        std::cin >> u >> v >> l;
        graph::addEdge(u, v, l);
        graph::addEdge(v, u, l);
    }
    for (int i = 1; i <= n; i++) graph::pas[i][i][i] = true;
    graph::DFS(1, 0);
    /*
    for (int k = 1; k <= m; k++) {
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= m; j++) {
                if (k == i) continue;
                if (k == j) continue;
                if (i == j) continue;
                graph::dis[i][j] = std::min(graph::dis[i][j], graph::dis[i][k] + graph::dis[k][j]);
                if (graph::dis[i][j] == graph::dis[i][k] + graph::dis[k][j]) {
                    graph::pas[i][j] = graph::pas[i][k] | graph::pas[k][j];
                }
            }
        }
    }
    */
    /*
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            printf("dis(%d, %d) = %d, pass: ", i, j, graph::dis[i][j]);
            for (int k = 1; k <= m; k++) if (graph::pas[i][j][k]) printf("%d ", k);
            printf("\n");
        }
    }
    */
    for (int i = 1; i <= m; i++) {
        int u = b[i];
        for (int j = 1; j <= m; j++) {
            int v = b[j];
            graph::vertex[u].dis = std::max(graph::vertex[u].dis, graph::dis[u][v]);
        }
        for (int j = 1; j <= m; j++) {
            int v = b[j];
            if(graph::dis[u][v] == graph::vertex[u].dis) graph::vertex[u].fri.push_back(v);
        }
    }
    int res = 0;
    int ans = 0;
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (graph::vertex[i].type) continue;
        res = 0;
        for (int j = 1; j <= m; j++) {
            int u = b[j];
            bool flag = true;
            for (auto v : graph::vertex[u].fri) {
                if (graph::pas[u][v][i] == false) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                res++;
                //printf("%d make %d unhappy\n", i, u);
            }
        }
        if (ans < res) {
            ans = res;
            cnt = 0;
        } 
        if (ans == res) cnt++;
    }
    std::cout << ans << ' ' << cnt << '\n';
    return 0;
}