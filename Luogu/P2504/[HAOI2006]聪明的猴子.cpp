#include <cstdio>
#include <cmath>
#include <algorithm>

const int maxm = 500 + 10;
const int maxn = 1000 + 10;
const int maxe = 1e6 + 10;

struct Graph {
    struct Vertex {
        int id;
        int x;
        int y;
    };

    struct Edge {
        Vertex u, v;
        double distance;

        bool operator<(const Edge &other) const {
            return distance < other.distance;
        }
    };

    struct DSU {
        int ancestor[maxn];

        void Init(const int &x) {
            ancestor[x] = x;
            return;
        }

        int Find(const int &x) {
            if (ancestor[x] == x) {
                return ancestor[x];
            } else {
                return ancestor[x] = Find(ancestor[x]);
            }
        }

        void Union(const int &x, const int &y) {
            int ancestorX = Find(x);
            int ancestorY = Find(y);

            if (ancestorX == ancestorY) {
                return;
            }

            ancestor[ancestorX] = ancestorY;
            return;
        }
    };

    Vertex tree[maxn];
    Edge edge[maxe];
    int ecnt;
    DSU dsu;

    Graph() {
        ecnt = 0;
    }

    double GetDistance(const Vertex &u, const Vertex &v) {
        int deltaX = abs(u.x - v.x);
        int deltaY = abs(u.y - v.y);
        double powerX = deltaX * deltaX;
        double powerY = deltaY * deltaY;
        return sqrt(powerX + powerY); 
    }

    void AddEdge(const Vertex &u, const Vertex &v) {
        ecnt++;
        edge[ecnt].u = u;
        edge[ecnt].v = v;
        edge[ecnt].distance = GetDistance(u, v);
        dsu.Init(u.id);
        dsu.Init(v.id);
        return;
    }

    void SortEdge() {
        std::sort(edge + 1, edge + ecnt + 1);
        return;
    }
};

int M;
int monkey[maxm];
int N;
Graph rainForest;

int main() {
    scanf("%d", &M);
    for (int i = 1; i <= M; i++) {
        scanf("%d", &monkey[i]);
    }
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        rainForest.tree[i].id = i;
        scanf("%d", &rainForest.tree[i].x);
        scanf("%d", &rainForest.tree[i].y);
    }

    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            rainForest.AddEdge(rainForest.tree[i], rainForest.tree[j]);
        }
    }

    rainForest.SortEdge();

    double maxPath = -1;
    int connected = 0;

    for (int i = 1; i <= rainForest.ecnt; i++) {
        int u = rainForest.edge[i].u.id;
        int v = rainForest.edge[i].v.id;
        int ancestorU = rainForest.dsu.Find(u);
        int ancestorV = rainForest.dsu.Find(v);

        if (ancestorU != ancestorV) {
            rainForest.dsu.Union(ancestorU, ancestorV);
            connected++;
            maxPath = std::max(maxPath, rainForest.edge[i].distance);
        }

        if (connected == N - 1) {
            break;
        }
    }

    int ans = 0;

    for (int i = 1; i <= M; i++) {
        if (monkey[i] >= maxPath) {
            ans++;
        }
    }

    printf("%d\n", ans);
    
    return 0;
}