#include <iostream>
#include <iomanip>
#include <queue>

typedef double dbl;
typedef std::deque<int> diq;

const int maxL = 1000;
const int maxP = 5000;
const int maxF = 1000;
const int maxT = 1000;
const dbl eps = 1e-3;

int l, p;
int f[maxL + 10];
int l1[maxP + 10], l2[maxP + 10], t[maxP + 10];
dbl mid;

namespace graph {
    struct Vertex {
        int head;
        int cnt;
        int vis;
        dbl dis;
    } vertex[maxL + 10];

    struct Edge {
        int head;
        int next;
        dbl weight;
    } edge[maxP + 10];
    
    int ecnt;

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        return;
    }

    bool SPFA() {
        diq q;
        for (int i = 1; i <= l; i++) vertex[i].cnt = 0;
        for (int i = 1; i <= l; i++) vertex[i].vis = false;
        for (int i = 1; i <= l; i++) vertex[i].dis = 0;
        for (int i = 1; i <= l; i++) q.push_back(i);
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            vertex[u].vis = false;
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                int w = edge[e].weight;
                if (vertex[v].dis > vertex[u].dis + mid * w - f[v]) {
                    vertex[v].dis = vertex[u].dis + mid * w - f[v];
                    vertex[v].cnt = vertex[u].cnt + 1;
                    if (vertex[v].cnt >= l) return false;
                    if (vertex[v].vis == false) q.push_back(v);
                    vertex[v].vis = true;
                }
            }
        }
        return true;
    }
}

int main() {
    std::cin >> l >> p;
    for (int i = 1; i <= l; i++) std::cin >> f[i];
    for (int i = 1; i <= p; i++) std::cin >> l1[i] >> l2[i] >> t[i], graph::addEdge(l1[i], l2[i], t[i]);
    dbl l = 0;
    dbl r = maxF;
    while (r - l >= eps) {
        mid = (l + r) / 2;
        if (graph::SPFA()) r = mid;
        else l = mid;
    }
    std::cout << std::setiosflags(std::ios::fixed);
    std::cout << std::setprecision(2) << l << '\n';
    return 0;
}