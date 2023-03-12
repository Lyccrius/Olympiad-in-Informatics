#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>

typedef long long lxl;
typedef std::vector<lxl> vic;
typedef std::deque<lxl> dic;

const lxl maxN = 1e6;

lxl n;
lxl a, l;
lxl ans;

namespace graph {
    struct Vertex {
        lxl head;
        lxl dfn;
        lxl low;
        lxl onr;
        lxl pre;
        lxl sum;
        lxl res;
        lxl max;
        lxl back;
        lxl ins;
    } vertex[maxN + 10];
    
    struct Edge {
        lxl tail;
        lxl head;
        lxl next;
        lxl weight;
    } edge[maxN * 2 + 10];

    lxl ecnt = 1;

    void addEdge(lxl tail, lxl head, lxl weight) {
        ecnt++;
        edge[ecnt].tail = tail;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        return;
    }

    lxl dfn;
    dic s;

    struct Ring {
        vic ver;
        vic pre;
    };

    std::vector<Ring> rings;

    void addR(lxl u) {
        Ring ring;
        lxl v;
        do {
            v = s.back();
            s.pop_back();
            if (vertex[v].ins) {
                ring.ver.push_back(v);
                ring.pre.push_back(vertex[v].pre);
                vertex[v].onr = true;
                vertex[v].ins = false;
            }
            //printf("%d: %d, pre = %d\n", u, v, vertex[v].pre);
            
        } while (v != u);
        rings.push_back(ring);
        return;
    }
    
    void DFS(lxl u, lxl from) {
        dfn++;
        vertex[u].dfn = dfn;
        vertex[u].low = dfn;
        vertex[u].ins = true;
        s.push_back(u);
        //printf("DFS %d from %d by %d at %d\n", u, edge[from].tail, from, dfn);
        for (lxl e = vertex[u].head; e; e = edge[e].next) {
            lxl v = edge[e].head;
            lxl w = edge[e].weight;
            //printf("%d to %d: e = %d\n", u, v, e);
            if (e == (from ^ 1)) continue;
            vertex[u].pre = w;
            //printf("pre[%d] = %d\n", u, vertex[u].pre);
            /*
            if (vertex[v].dfn) {
                vertex[u].low = std::min(vertex[u].low, vertex[v].dfn);
                if (!vertex[u].back) {
                    vertex[u].back = v;
                    vertex[u].pre = w;
                }
            } else {
                DFS(v, e);
                vertex[u].low = std::min(vertex[u].low, vertex[v].low);
                if (!vertex[u].back && vertex[v].back) {
                    vertex[u].back = vertex[v].back;
                    vertex[u].pre = w;
                }
            }
            */
            if (vertex[v].dfn) {
                if (vertex[v].ins) addR(v);
            } else DFS(v, e);
        }
        vertex[u].ins = false;
        //printf("low[%d] = %d\n", u, vertex[u].low);
        //printf("dfn[%d] = %d\n", u, vertex[u].dfn);
        //printf("back[%d] = %d\n", u, vertex[u].back);
        //if (vertex[u].dfn == vertex[u].low) {
        //    if (vertex[u].back == u) {
        //        addR(u);
        //    } else {
        //        s.pop_back();
        //    }
        //}
        return;
    }

    void DP(lxl u, lxl from) {
        //printf("DP %d from %d\n", u, edge[from].tail);
        for (lxl e = vertex[u].head; e; e = edge[e].next) {
            lxl v = edge[e].head;
            lxl w = edge[e].weight;
            if (e == (from ^ 1)) continue;
            if (vertex[v].onr) continue;
            DP(v, e);
            vertex[u].res = std::max(vertex[u].res, vertex[v].res);
            vertex[u].res = std::max(vertex[u].res, vertex[v].sum + w + vertex[u].sum);
            vertex[u].sum = std::max(vertex[u].sum, vertex[v].sum + w);
        }
        //printf("dia[%d] = %d\n", u, vertex[u].res);
        return;
    }

    lxl pre[maxN * 2 + 10];
    lxl sum[maxN * 2 + 10];
    dic q;

    lxl solve(Ring ring) {
        lxl size = ring.ver.size() * 2;
        lxl ret = 0;
        q.clear();
        for (int i = 0; i < ring.ver.size(); i++) ret = std::max(ret, vertex[ring.ver[i]].res);
        for (lxl i = 0; i < ring.ver.size(); i++) pre[i + 1] = ring.pre[i];
        for (lxl i = 0; i < ring.ver.size(); i++) sum[i + 1] = vertex[ring.ver[i]].sum;
        for (lxl i = 1; i <= ring.ver.size(); i++) pre[i + ring.ver.size()] = pre[i];
        for (lxl i = 1; i <= ring.ver.size(); i++) sum[i + ring.ver.size()] = sum[i];
        for (lxl i = 1; i <= size; i++) pre[i] += pre[i - 1];
        
    //for (lxl i = 0; i < ring.ver.size(); i++) printf("%lld ", ring.ver[i]); printf("\n");
    //for (lxl i = 1; i <= size; i++) printf("%lld ", pre[i]); printf("\n");
    //for (lxl i = 1; i <= size; i++) printf("%lld ", sum[i]); printf("\n");
    //printf("\n");

        for (lxl i = 1; i <= size; i++) {
            if (q.size() && i - q.front() >= ring.ver.size()) q.pop_front();
            if (q.size()) ret = std::max(ret, sum[q.front()] - pre[q.front()] + sum[i] + pre[i]);
            while (q.size() && sum[q.back()] - pre[q.back()] <= sum[i] - pre[i]) q.pop_back();
            q.push_back(i);
        }
        //printf("%lld\n", ret);
        //printf("\n");
        //printf("\n");
        return ret;
    }

    void mian() {
        for (auto ring : rings) ans += solve(ring);
        return;
    }
}

int main() {
    std::cin >> n;
    //for (int i = 1; i <= n; i++) graph::vertex[i].head = -1;
    for (lxl i = 1; i <= n; i++) std::cin >> a >> l, graph::addEdge(i, a, l), graph::addEdge(a, i, l);
    for (lxl i = 1; i <= n; i++) if (!graph::vertex[i].dfn) graph::DFS(i, 0);
    for (lxl i = 1; i <= n; i++) if (graph::vertex[i].onr) graph::DP(i, 0);
    //for (int i = 1; i <= n; i++) printf("sum[%d] = %lld\n", i, graph::vertex[i].sum);
    graph::mian();
    std::cout << ans;
    return 0;
}