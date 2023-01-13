#include <cstdio>
#include <algorithm>
#include <set>

const int maxN = 1e5;
const int maxM = 2e5;

int n, m;
int u[maxM + 10], v[maxM + 10];

long long ans;

namespace Graph {
    struct Vertex {
        int head;
        int degree;
        int vis;
    } vertex[maxN + 10];

    struct Edge {
        int tail;
        int head;
        int next;
    } edge[maxM + 10];

    int ecnt;

    void AddEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].tail = tail;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void solve() {
        for (int u = 1; u <= n; u++) {
            for (int eu = vertex[u].head; eu; eu = edge[eu].next) {
                int v = edge[eu].head;
                vertex[v].vis = u;
            }
            for (int eu = vertex[u].head; eu; eu = edge[eu].next) {
                int v = edge[eu].head;
                for (int ev = vertex[v].head; ev; ev = edge[ev].next) {
                    int w = edge[ev].head;
                    if (vertex[w].vis == u) ans++;
                }
            }
        }
        return;
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) scanf("%d%d", &u[i], &v[i]), Graph::vertex[u[i]].degree++, Graph::vertex[v[i]].degree++;
    for (int i = 1; i <= m; i++) if (Graph::vertex[u[i]].degree > Graph::vertex[v[i]].degree || (Graph::vertex[u[i]].degree == Graph::vertex[v[i]].degree && u[i] > v[i])) std::swap(u[i], v[i]);
    for (int i = 1; i <= m; i++) Graph::AddEdge(u[i], v[i]);
    Graph::solve();
    printf("%lld\n", ans);
    return 0;
}