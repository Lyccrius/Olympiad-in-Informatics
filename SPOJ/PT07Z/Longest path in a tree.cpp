#include <cstdio>
#include <algorithm>

const int maxn = 1e4 + 10;
const int maxm = 1e4 + 10;

struct Graph {
    struct Vertex {
        int ocnt;
        int out[maxn];
        int distance1;
        int distance2;
    };

    struct Edge {
        int head;
    };

    Vertex vertex[maxn];
    Edge edge[maxm << 1];
    int ecnt;

    void AddEdge(int u, int v) {
        ecnt++;
        edge[ecnt].head = v;
        vertex[u].ocnt++;
        vertex[u].out[vertex[u].ocnt] = ecnt;
        return;
    }

    int diameter;

    void DFS(int u, int from) {
        for (int i = 1; i <= vertex[u].ocnt; i++) {
            int v = edge[vertex[u].out[i]].head;
            if (v == from) {
                continue;
            }

            DFS(v, u);
            int distanceV = vertex[v].distance1 + 1;
            if (distanceV > vertex[u].distance1) {
                vertex[u].distance2 = vertex[u].distance1;
                vertex[u].distance1 = distanceV;
            } else 
            if (vertex[u].distance2 < distanceV) {
                vertex[u].distance2 = distanceV;
            }

            diameter = std::max(diameter, 
            vertex[u].distance1 + 
            vertex[u].distance2);
        }

        return;
    }
};

int N;
Graph tree;

int main() {
    scanf("%d", &N);
    for (int i = 1; i < N; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        tree.AddEdge(u, v);
        tree.AddEdge(v, u);
    }

    tree.DFS(1, 0);
    printf("%d\n", tree.diameter);

    return 0;
}