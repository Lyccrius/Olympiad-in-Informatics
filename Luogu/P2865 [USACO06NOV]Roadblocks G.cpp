#include <iostream>
#include <queue>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;  
}

const int maxN = 100000;
const int maxR = 200000;
const int inf = 1e9;

int N, R;
int A, B, D;

namespace graph {
    struct Vertex {
        int head;
        int dis1;
        int dis2;
    } vertex[maxN + 10];
    
    struct Edge {
        int head;
        int next;
        int weight;
    } edge[maxR * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        return;
    }

    struct Node {
        int vertex;
        int dis;

        bool operator<(const Node &other) const {
            return dis > other.dis;
        }
    };

    void Dijkstra(int s) {
        for (int i = 1; i <= N; i++) vertex[i].dis1 = inf, vertex[i].dis2 = inf;
        vertex[s].dis1 = 0;
        std::priority_queue<Node> q;
        q.push((Node) {s, 0});
        while (!q.empty()) {
            int u = q.top().vertex;
            int d = q.top().dis;
            q.pop();
            if (d > vertex[u].dis2) continue;
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                int w = edge[e].weight;
                if (vertex[v].dis1 > d + w) {
                    vertex[v].dis2 = vertex[v].dis1;
                    vertex[v].dis1 = d + w;
                    q.push((Node) {v, vertex[v].dis1});
                }
                if (vertex[v].dis2 > d + w && vertex[v].dis1 < d + w) {
                    vertex[v].dis2 = d + w;
                    q.push((Node) {v, vertex[v].dis2});
                }
            }
        }
        return;
    }
}

int main() {
    promote();
    std::cin >> N >> R;
    for (int i = 1; i <= R; i++) std::cin >> A >> B >> D, graph::addEdge(A, B, D), graph::addEdge(B, A, D);
    graph::Dijkstra(1);
    std::cout << graph::vertex[N].dis2;
    return 0;
}