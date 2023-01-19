#include <iostream>
#include <algorithm>
#include <vector>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int mod = 10007;
const int maxN = 2e5;
const int maxW = 1e4;

int n;
int u[maxN + 10], v[maxN + 10];
int W[maxN + 10];
int ans;
int sum;

namespace graph {
    struct Vertex {
        int head;
        int ans;
        int sum;
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
        ans = std::max(ans, vertex[tail].ans * W[head]);
        sum = (sum + vertex[tail].sum * W[head]) % mod;
        vertex[tail].ans = std::max(vertex[tail].ans, W[head]);
        vertex[tail].sum = (vertex[tail].sum + W[head]) % mod;
        return;
    }

    void mian() {
        for (int i = 1; i < n; i++) addEdge(u[i], v[i]), addEdge(v[i], u[i]);
        std::cout << ans << ' ' << (sum * 2) % mod;
    }
}

int main() {
    std::cin >> n;
    for (int i = 1; i < n; i++) std::cin >> u[i] >> v[i];
    for (int i = 1; i <= n; i++) std::cin >> W[i];
    graph::mian();
    return 0;
}