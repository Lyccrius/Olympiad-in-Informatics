#include <cstdio>
#include <queue>

const int maxN = 1000 + 10;

int N;

namespace Magic {
    struct Vertex {
        int u;
        int cost;
        unsigned long long plan;
        bool relaxed;
        int head;

        bool operator<(Vertex other) const {
            return cost > other.cost;
        }
    };

    struct Edge {
        int u;
        int head;
        int next;
    };

    Vertex potion[maxN];
    Edge config[2 * maxN * maxN];
    int ecnt;

    void AddEdge(int u1, int u2, int v) {
        ecnt++;
        config[ecnt].u = u2;
        config[ecnt].head = v;
        config[ecnt].next = potion[u1].head;
        potion[u1].head = ecnt;
        potion[u1].u = u1;
        potion[u2].u = u2;
        return;
    }

    void Dijkstra() {
        std::priority_queue<Vertex> waiting;
        for (int i = 0; i < N; i++) {
            waiting.push(potion[i]);
            potion[i].plan = 1;
        }
        while (!waiting.empty()) {
            int u1 = waiting.top().u;
            int cost = waiting.top().cost;
            waiting.pop();
            if (cost != potion[u1].cost) continue;
            potion[u1].relaxed = true;
            for (int i = potion[u1].head; i; i = config[i].next) {
                int u2 = config[i].u;
                int v = config[i].head;
                if (potion[u2].relaxed) {
                    if (potion[v].cost > potion[u1].cost + potion[u2].cost) {
                        potion[v].cost = potion[u1].cost + potion[u2].cost;
                        waiting.push(potion[v]);
                    }
                    if (potion[v].cost == potion[u1].cost + potion[u2].cost) {
                        potion[v].plan += potion[u1].plan * potion[u2].plan;
                    }
                }
            }
        }
        return;
    }
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) scanf("%d", &Magic::potion[i].cost);
    int A, B, C;
    while (scanf("%d%d%d", &A, &B, &C) != EOF) {
        Magic::AddEdge(A, B, C);
        if (A == B) continue;
        Magic::AddEdge(B, A, C);
    }
    Magic::Dijkstra();
    printf("%d %llu\n", Magic::potion[0].cost, Magic::potion[0].plan);
    return 0;
}