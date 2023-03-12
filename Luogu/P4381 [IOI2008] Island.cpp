#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>

typedef long long lxl;
typedef std::deque<lxl> dic;
typedef std::vector<lxl> vic;

const int maxN = 1e6;

int n;
int a, l;
lxl ans;

namespace graph {
    struct Vertex {
        int head;
        int vis;
        int ins;
        int onr;
        lxl pre;
        lxl sum;
        lxl res;
    } vertex[maxN + 10];
    
    struct Edge {
        int head;
        int next;
        int weight;
    } edge[maxN * 2 + 10];

    int ecnt = 1;

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        return;
    }

    dic s;

    struct Ring {
        vic ver;
        vic pre;
    };

    std::vector<Ring> rings;

    void addR(lxl u) {
        Ring ring;
        int v;
        do {
            v = s.back();
            s.pop_back();
            if (vertex[v].ins) {
                ring.ver.push_back(v);
                ring.pre.push_back(vertex[v].pre);
                vertex[v].ins = false;
                vertex[v].onr = true;
            }
        } while (v != u);
        rings.push_back(ring);
        return;
    }
    
    void DFS(int u, int from) {
        vertex[u].vis = true;
        vertex[u].ins = true;
        s.push_back(u);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            vertex[u].pre = w;
            if (e == (from ^ 1)) continue;
            if (vertex[v].vis) {
                if (vertex[v].ins) addR(v);
            } else DFS(v, e);
        }
        vertex[u].ins = false;
        return;
    }

    void DP(int u, int from) {
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (e == (from ^ 1)) continue;
            if (vertex[v].onr) continue;
            DP(v, e);
            vertex[u].res = std::max(vertex[u].res, vertex[v].res);
            vertex[u].res = std::max(vertex[u].res, vertex[v].sum + w + vertex[u].sum);
            vertex[u].sum = std::max(vertex[u].sum, vertex[v].sum + w);
        }
        return;
    }

    lxl pre[maxN * 2 + 10];
    lxl sum[maxN * 2 + 10];
    dic q;

    lxl solve(Ring ring) {
        int size = ring.ver.size() * 2;
        lxl ret = 0;
        q.clear();
        for (int i = 0; i < ring.ver.size(); i++) ret = std::max(ret, vertex[ring.ver[i]].res);
        for (int i = 0; i < ring.ver.size(); i++) pre[i + 1] = ring.pre[i];
        for (int i = 0; i < ring.ver.size(); i++) sum[i + 1] = vertex[ring.ver[i]].sum;
        for (int i = 1; i <= ring.ver.size(); i++) pre[i + ring.ver.size()] = pre[i];
        for (int i = 1; i <= ring.ver.size(); i++) sum[i + ring.ver.size()] = sum[i];
        for (int i = 1; i <= size; i++) pre[i] += pre[i - 1];
        for (int i = 1; i <= size; i++) {
            if (q.size() && i - q.front() >= ring.ver.size()) q.pop_front();
            if (q.size()) ret = std::max(ret, sum[q.front()] - pre[q.front()] + sum[i] + pre[i]);
            while (q.size() && sum[q.back()] - pre[q.back()] <= sum[i] - pre[i]) q.pop_back();
            q.push_back(i);
        }
        return ret;
    }

    void mian() {
        for (auto ring : rings) ans += solve(ring);
        return;
    }
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a >> l, graph::addEdge(i, a, l), graph::addEdge(a, i, l);
    for (int i = 1; i <= n; i++) if (!graph::vertex[i].vis) graph::DFS(i, 0);
    for (int i = 1; i <= n; i++) if (graph::vertex[i].onr) graph::DP(i, 0);
    graph::mian();
    std::cout << ans;
    return 0;
}