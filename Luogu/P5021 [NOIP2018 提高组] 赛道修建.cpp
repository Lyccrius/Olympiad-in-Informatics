#include <iostream>
#include <vector>
#include <algorithm>

const int maxN = 5e4;
const int maxM = 5e4;
const int maxL = 1e4;

int n, m;
int a[maxN + 10], b[maxN + 10], l[maxN + 10];
int res;

namespace graph {
    struct Vertex {
        int head;
        int weight;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        int weight;
    } edge[maxM * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        return;
    }

    int tag[maxN + 10];

    void init() {
        for (int u = 0; u <= n; u++) vertex[u].weight = 0;
        for (int e = 0; e <= n; e++) tag[e] = 0;
        return;
    }

    void DFS(int u, int from, int lim) {
        std::vector<int> q;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u, lim);
        }
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == from) continue;
            q.push_back(vertex[v].weight + w);
        }
        std::sort(q.begin(), q.end());
        while (!q.empty() && q.back() >= lim) {
            q.pop_back();
            res--;
        }
        for (int i = 0; i < q.size(); i++) {
            if (tag[i] != u) {
                int p = std::lower_bound(q.begin() + i + 1, q.end(), lim - q[i]) - q.begin();
                while (p < q.size() && tag[p] == u) p++;
                if (p < q.size()) {
                    tag[i] = u;
                    tag[p] = u;
                    res--;
                }
            }
        }
        for (int i = q.size() - 1; i >= 0; i--) {
            if (tag[i] != u) {
                vertex[u].weight = q[i];
                break;
            }
        }
        return;
    }
}

bool check(int x) {
    graph::init();
    graph::DFS(1, 0, x);
    return res > 0;
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i < n; i++) {
        std::cin >> a[i] >> b[i] >> l[i];
        graph::addEdge(a[i], b[i], l[i]);
        graph::addEdge(b[i], a[i], l[i]);
    }
    int l = 0;
    int r = maxM * maxL;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        res = m;
        if (check(mid)) r = mid - 1;
        else l = mid;
    }
    std::cout << l;
    return 0;
}