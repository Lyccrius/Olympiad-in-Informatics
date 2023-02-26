#include <iostream>
#include <algorithm>

const int maxN = 2e5;
const int inf = 2e6;

int t;
int n;
int c[maxN + 10];
int u, v;
int ans;

namespace tree {
    struct Vertex {
        int fa;
        int head;
        int status;
        int son;
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

    void init() {
        for (int i = 1; i <= n; i++) vertex[i].head = 0;
        for (int i = 1; i <= n; i++) vertex[i].status = 0;
        for (int i = 1; i <= n; i++) vertex[i].son = inf;
        ecnt = 0;
        ans = inf;
        return;
    }

    void DFS(int u, int from) {
        vertex[u].fa = from;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u);
        }
        return;