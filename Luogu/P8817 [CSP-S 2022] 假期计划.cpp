#include <cstdio>
#include <queue>

#define A 1

const int maxn = 2500 + 10;
const int maxm = 1e5 + 10;

int n, m, k;

namespace Graph {
    struct Vertex {
        int distance;
        int head;
        long long score;
    };

    struct Edge {
        int head;
        int next;
    };

    Vertex vertex[maxn];
    Edge edge[maxm << 1];
    int ecnt;

    void AddEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    bool adjacency[maxn][maxn];

    void BellmanFord() {
        for (int s = 1; s <= n; s++) {
            for (int u = 1; u <= n; u++) {
                vertex[u].distance = -1;
            }
            std::queue<int> waiting;
            waiting.push(s);
            while (!waiting.empty()) {
                int u = waiting.front();
                waiting.pop();
                for (int e = vertex[u].head; e; e = edge[e].next) {
                    int v = edge[e].head;
                    if (vertex[v].distance == -1) {
                        vertex[v].distance = vertex[u].distance + 1;
                        waiting.push(v);
                    }
                }
            }
            for (int u = 1; u <= n; u++) {
                if (vertex[u].distance != -1 && 
                    vertex[u].distance <= k) {
                    adjacency[s][u] = true;
                }
            }
        }
        return;
    }

    int maxB[maxn][5];

    void PreWork() {
        for (int C = 2; C <= n; C++) {
            for (int B = 2; B <= n; B++) {
                if (B ^ C && 
                    adjacency[A][B] && 
                    adjacency[B][C]) {
                    int nowB = B;
                    for (int i = 1; i <= 3; i++) {
                        if (vertex[nowB].score > 
                            vertex[maxB[C][i]].score) {
                            std::swap(nowB, maxB[C][i]);
                        }
                    }
                }
            }
        }
        return;
    }

    long long ans;

    void Solve() {
        for (int C = 2; C <= n; C++) {
            for (int D = C + 1; D <= n; D++) {
                if (!adjacency[C][D]) {
                    continue;
                }
                for (int i = 1; i <= 3; i++) {
                    for (int j = 1; j <= 3; j++) {
                        int B = maxB[C][i];
                        int E = maxB[D][j];
                        if (B && E && B != E && 
                            B != D && C != E) {
                            ans = std::max(ans, vertex[B].score + vertex[C].score 
                                              + vertex[D].score + vertex[E].score);
                        }
                    }
                }
            }
        }
        return;
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 2; i <= n; i++) scanf("%lld", &Graph::vertex[i].score);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        Graph::AddEdge(u, v);
        Graph::AddEdge(v, u);
    }

    Graph::BellmanFord();
    Graph::PreWork();
    Graph::Solve();

    printf("%lld\n", Graph::ans);

    return 0;
}