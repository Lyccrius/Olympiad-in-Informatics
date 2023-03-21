#include <iostream>
#include <algorithm>

const int maxN = 2000;

int N, K;
int A[maxN + 10], B[maxN + 10];

namespace graph {
    struct Vertex {
        int head;
        int dis;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxN * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void DFS(int u, int from) {
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            vertex[v].dis = vertex[u].dis + 1;
            DFS(v, u);
        }
        return;
    }
}

namespace even {
    void mian() {
        int cnt = 0;
        int ans = N - 1;
        for (int u = 1; u <= N; u++) {
            graph::vertex[u].dis = 0;
            graph::DFS(u, 0);
            cnt = 0;
            for (int v = 1; v <= N; v++) {
                if (graph::vertex[v].dis > K / 2) {
                    cnt++;
                }
            }
            ans = std::min(ans, cnt);
        }
        std::cout << ans;
        return;
    }
}

namespace odd {
    void mian() {
        int cnt = 0;
        int ans = N - 1;
        for (int e = 1; e < N; e++) {
            int u = A[e];
            int v = B[e];
            graph::vertex[u].dis = 0;
            graph::vertex[v].dis = 0;
            graph::DFS(u, v);
            graph::DFS(v, u);
            cnt = 0;
            for (int w = 1; w <= N; w++) {
                if (graph::vertex[w].dis > K / 2) {
                    cnt++;
                }
            }
            ans = std::min(ans, cnt);
        }
        std::cout << ans;
        return;
    }
}

int main() {
    std::cin >> N >> K;
    for (int i = 1; i < N; i++) {
        std::cin >> A[i] >> B[i];
        graph::addEdge(A[i], B[i]);
        graph::addEdge(B[i], A[i]);
    }
    if (K & 1) odd::mian();
    else even::mian();
    return 0;
}