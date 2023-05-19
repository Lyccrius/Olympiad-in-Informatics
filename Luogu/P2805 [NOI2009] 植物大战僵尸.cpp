#include <iostream>
#include <deque>

typedef std::deque<int> diq;

const int maxN = 20;
const int maxM = 30;
const int maxS = 1e4;
const int inf = 1e9 + 10;

int n, m;
int s[maxN + 10][maxM + 10];
int w, r, c;

namespace graph {
    struct Vertex {
        int head;
        int ideg;
        int rank;
    } vertex[maxN * maxM + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxN * maxM + maxN * maxM * maxN * maxM + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        vertex[head].ideg++;
        return;
    }

    namespace flow {
        struct Vertex {
            int head;
            int dis;
            int cur;

            Vertex() {
                head = -1;
                return;
            }
        } vertex[maxN * maxM + 10];

        struct Edge {
            int head;
            int next;
            int flow;
            int capacity;
        } edge[2 * (maxN + maxM + maxN * maxM + maxN * maxM * maxN * maxM) + 10];

        int ecnt;

        void addEdge(int tail, int head, int capcacity) {
            edge[ecnt].head = head;
            edge[ecnt].next = vertex[tail].head;
            edge[ecnt].capacity = capcacity;
            vertex[tail].head = ecnt;
            ecnt++;
            edge[ecnt].head = tail;
            edge[ecnt].next = vertex[head].head;
            edge[ecnt].capacity = 0;
            vertex[head].head = ecnt;
            ecnt++;
            return;
        }

        bool BFS(int s, int t) {
            diq q;
            for (int u = 0; u <= n * m + 2; u++) vertex[u].dis = inf;
            vertex[s].dis = 0;
            q.push_back(s);
            while (!q.empty()) {
                int u = q.front();
                q.pop_front();
                for (int e = vertex[u].head; ~e; e = edge[e].next) {
                    int v = edge[e].head;
                    if (edge[e].capacity == edge[e].flow) continue;
                    if (vertex[v].dis > vertex[u].dis + 1) {
                        vertex[v].dis = vertex[u].dis + 1;
                        q.push_back(v);
                    }
                }
            }
            return vertex[t].dis < inf;
        }

        int DFS(int u, int t, int lim) {
            if (u == t) return lim;
            if (!lim) return lim;
            int ret = 0;
            for (int &e = vertex[u].cur; ~e; e = edge[e].next) {
                int v = edge[e].head;
                int w = edge[e].capacity - edge[e].flow;
                if (vertex[v].dis != vertex[u].dis + 1) continue;
                int flow = DFS(v, t, std::min(lim - ret, w));
                ret += flow;
                edge[e].flow += flow;
                edge[e ^ 1].flow -= flow;
                if (ret == lim) break;
            }
            return ret;
        }

        int Dinic(int s, int t) {
            int ret = 0;
            while (BFS(s, t)) {
                for (int u = 0; u <= n * m + 2; u++) vertex[u].cur = vertex[u].head;
                ret += DFS(s, t, inf);
            }
            return ret;
        }
    }

    diq topo;
    int sum;

    void TopoSort() {
        diq q;
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (vertex[i * m + j].ideg == 0) q.push_back(i * m + j);
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            vertex[u].rank = topo.size();
            topo.push_back(u);
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                vertex[v].ideg--;
                if (vertex[v].ideg == 0) q.push_back(v);
            }
        }
        for (auto u : topo) {
            if (s[u / m][u % m] > 0) flow::addEdge(n * m + 1, u, s[u / m][u % m]), sum += s[u / m][u % m];
            if (s[u / m][u % m] < 0) flow::addEdge(u, n * m + 2, - s[u / m][u % m]);
            for (int e = vertex[u].head; e; e = edge[e].next) flow::addEdge(edge[e].head, u, inf);
        }
        return;
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> s[i][j];
            std::cin >> w;
            if (j) graph::addEdge(i * m + j, i * m + j - 1);
            while (w--) std::cin >> r >> c, graph::addEdge(i * m + j, r * m + c);
        }
    }
    graph::TopoSort();
    std::cout << graph::sum - graph::flow::Dinic(n * m + 1, n * m + 2) << '\n';
    return 0;
}