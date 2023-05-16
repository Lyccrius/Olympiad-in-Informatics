#include <iostream>
#include <deque>

typedef double dbl;
typedef std::deque<int> diq;

const int maxN = 1000;
const int maxS = 1000;
const int maxT = 1000;
const int maxK = 10;
const dbl eps = 1e-4;

int n, s, t;
int o, A, B, k;
int C, x;
dbl T, l, r = maxK;

namespace graph {
    struct Vertex {
        int head;
        int cnt;
        int vis;
        dbl dis;

        Vertex() {
            head = -1;
            return;
        }
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        int type;
        dbl weight;
    } edge[maxS + 2 * maxT + 10];

    int ecnt;

    void addEdge(int tail, int head, dbl weight, int type) {
        edge[ecnt].head = head;
        edge[ecnt].type = type;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        ecnt++;
        return;
    }

    bool SPFA(int s) {
        diq q;
        for (int i = 0; i <= n; i++) vertex[i].vis = false;
        for (int i = 0; i <= n; i++) vertex[i].dis = 0;
        for (int i = 0; i <= n; i++) vertex[i].cnt = 0;
        vertex[s].dis = 1;
        q.push_back(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            vertex[u].vis = false;
            for (int e = vertex[u].head; ~e; e = edge[e].next) {
                int v = edge[e].head;
                dbl w = edge[e].weight;
                if (edge[e].type == 1) w = w - T;
                if (edge[e].type == 2) w = 1.0 / (w + T);
                if (vertex[v].dis < vertex[u].dis * w) {
                    vertex[v].dis = vertex[u].dis * w;
                    vertex[v].cnt = vertex[u].cnt + 1;
                    if (vertex[v].cnt > n) return false;
                    if (vertex[v].vis == false) {
                        vertex[v].vis = true;
                        q.push_back(v);
                    }
                }
            }
        }
        return true;
    }
}

int main() {
    std::cin >> n >> s >> t;
    for (int i = 1; i <= s; i++) {
        std::cin >> o >> A >> B >> k;
        graph::addEdge(B, A, k, o);
        if (o == 1) r = std::min(r, 1.0 * k);
    }
    for (int i = 1; i <= t; i++) {
        std::cin >> C >> x;
        graph::addEdge(0, C, x, 0);
        graph::addEdge(C, 0, 1.0 / x, 0);
    }
    if (graph::SPFA(0)) {
        std::cout << -1 << '\n';
        return 0;
    }
    while (r - l >= eps) {
        T = (l + r) / 2;
        if (graph::SPFA(0)) r = T;
        else l = T;
    }
    std::cout << l << '\n';
    return 0;
}