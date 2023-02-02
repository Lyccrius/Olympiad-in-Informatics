#include <iostream>
#include <algorithm>
#include <vector>

const int maxN = 3e5;

int n, s;
int u, v, w;
int p;
int q;
int d;

namespace graph {
    struct Vertex {
        int head;
        int pre;
        int dis;
        int ond;
        int fa;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        int weight;
    } edge[maxN * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].weight = weight;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void DFS(int u, int from) {
        //printf("DFS %d from %d, %d\n", u, from, vertex[u].dis);
        vertex[u].fa = from;
        d = std::max(d, vertex[u].dis);
        if (vertex[p].dis < vertex[u].dis) p = u;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (v == from) continue;
            if (vertex[v].ond) continue;
            vertex[v].dis = vertex[u].dis + w;
            //vertex[v].ond |= vertex[u].ond;
            DFS(v, u);
        }
        return;
    }

    std::vector<int> dia;

    bool check(int x) {
        //printf("checking %d\n", x);
        int l = 0;
        int r = dia.size() - 1;
        while (l + 1 < dia.size() && dia.front() - dia[l + 1] <= x) {
            //printf("vertex[%d].pre = %d\n", dia[l + 1], vertex[dia[l + 1]].pre);
            l++;
        }
        while (r - 1 > 0 && dia[r - 1] <= x) {
            //printf("vertex[%d].pre - vertex[%d].pre = %d\n", dia.back(), vertex[r - 1].p)
            r--;
        }
        //printf("found %d, %d\n", dia[l], dia[r]);
        return vertex[dia[r]].pre - vertex[dia[l]].pre <= x;
    }

    void mian() {
        for (int u = p; u; u = vertex[u].fa) dia.push_back(vertex[u].dis);
        for (int u = p; u; u = vertex[u].fa) vertex[u].ond = true;
        for (int u = p; u; u = vertex[u].fa) vertex[u].pre = vertex[u].dis;
        for (int u = p; u; u = vertex[u].fa) vertex[u].dis = 0, DFS(u, vertex[u].fa);
        //std::reverse(dia.begin(), dia.end());
        int l = 0;
        int r = vertex[dia.back()].pre;
        for (int u = 1; u <= n; u++) l = std::max(l, vertex[u].dis);
        //printf("l = %d, r = %d\n", l, r);
        while (l < r) {
            //printf("%d, %d\n", l, r);
            int mid = (l + r) / 2;
            if (check(mid)) r = mid;
            else l = mid + 1;
        }
        std::cout << l;
        return;
    }
}

int main() {
    std::cin >> n >> s;
    for (int i = 1; i < n; i++) std::cin >> u >> v >> w, graph::addEdge(u, v, w), graph::addEdge(v, u, w);
    p = 1;
    graph::vertex[p].dis = 0;
    graph::DFS(p, 0);
    graph::vertex[p].dis = 0;
    graph::DFS(p, 0);
    //printf("dismeter: %d to %d\n", p, q);
    graph::mian();
    return 0;
}