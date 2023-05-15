#include <iostream>
#include <algorithm>
#include <deque>

typedef std::deque<int> diq;

const int maxN = 1e5;

int n;
int u, v;

namespace graph {
    struct Vertex {
        int head;
        int next;
        int left;
        int res;

        Vertex() {
            head = -1;
            return;
        }
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[2 * maxN + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        ecnt++;
        return;
    }

    void DFS(int u, int from, int k) {
        vertex[u].res = 0;
        diq q;
        for (int e = vertex[u].head; ~e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u, k);
            vertex[u].res += vertex[v].res;
            q.push_back(vertex[v].left);
        }
        q.push_back(0);
        q.push_back(0);
        std::sort(q.begin(), q.end());
        vertex[u].left = q.back() + 1;
        while (q.size() >= 2) {
            if (q.front() + q.back() + 1 >= k) {
                q.pop_back();
                vertex[u].left = 0;
                vertex[u].res++;
                break;
            }
            q.pop_front();
        }
        return;
    }
}

int solve(int k) {
    graph::DFS(1, 0, k);
    return graph::vertex[1].res;
}

int main() {
    std::cin >> n;
    for (int i = 1; i < n; i++) {
        std::cin >> u >> v;
        graph::addEdge(u, v);
        graph::addEdge(v, u);
    }
    for (int k = 1; k <= n; k++) std::cout << solve(k) << '\n';
    return 0;
}