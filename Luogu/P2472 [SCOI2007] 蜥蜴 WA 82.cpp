#include <iostream>
#include <deque>

typedef char chr;
typedef std::deque<int> diq;

const int maxR = 20;
const int maxC = 20;
const int maxD = 4;
const int maxH = 3;
const int maxL = 400;

int r, c, d, l;
chr a[maxR + 10][maxC + 10];
chr b[maxR + 10][maxC + 10];

namespace graph {
    struct Vertex {
        int head;
        int vis;
        int dis;
        int cur;

        Vertex() {
            head = -1;
            return;
        }
    } vertex[2 * maxR * maxC + 10];

    struct Edge {
        int head;
        int next;
        int flow;
        int capacity;
    } edge[2 * (2 * maxR * maxC + maxR * maxC * maxR * maxC + 2 * maxR * maxD + 2 * maxC * maxD) + 10];

    int ecnt;

    void addEdge(int tail, int head, int capacity) {
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].capacity = capacity;
        vertex[tail].head = ecnt;
        ecnt++;
        edge[ecnt].head = tail;
        edge[ecnt].next = vertex[head].head;
        edge[ecnt].capacity = 0;
        vertex[head].head = ecnt;
        ecnt++;
        return;
    }

    bool BFS(int s, int t) {
        diq q;
        for (int u = 0; u <= 2 * r * c + 1; u++) vertex[u].vis = false;
        for (int u = 0; u <= 2 * r * c + 1; u++) vertex[u].dis = maxL;
        vertex[s].dis = 0;
        q.push_back(s);
        while (!q.empty()) {
            int u = q.front();
            if (vertex[u].vis) continue;
            vertex[u].vis = true;
            q.pop_front();
            for (int e = vertex[u].head; ~e; e = edge[e].next) {
                int v = edge[e].head;
                if (edge[e].flow == edge[e].capacity) continue;
                if (vertex[v].dis > vertex[u].dis + 1) {
                    vertex[v].dis = vertex[u].dis + 1;
                    q.push_back(v);
                }
            }
        }
        return vertex[t].dis < maxL;
    }

    int DFS(int u, int t, int lim) {
        if (u == t) return lim;
        if (!lim) return lim;
        int ret = 0;
        for (int &e = vertex[u].cur; ~e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].capacity - edge[e].flow;
            if (vertex[v].dis != vertex[u].dis + 1) continue;
            int flow = DFS(v, t, std::min(lim - ret, w));
            ret += flow;
            edge[e].flow += flow;
            edge[e ^ 1].flow -= flow;
            if (ret == lim) break;
        }
        return ret;
    }

    int Dinic(int s, int t) {
        int ret = 0;
        while (BFS(s, t)) {
            for (int u = 0; u <= 2 * r * c + 1; u++) vertex[u].cur = vertex[u].head;
            ret += DFS(s, t, maxL);
        }
        return ret;
    }
}

int id(int i, int j, int k) {
    return (i - 1) * r + j + k * r * c;
}

bool check(int i, int j, int ii, int jj) {
    if (i == ii && j == jj) return false;
    if (ii < 1 || ii > r) return false;
    if (jj < 1 || jj > c) return false;
    int di = ii - i;
    int dj = jj - j;
    if (di * di + dj * dj > d * d) return false;
    //printf("(%d, %d) skip to (%d, %d)\n", i, j, ii, jj);
    return true;
}

int main() {
    std::cin >> r >> c >> d;
    for (int i = 1; i <= r; i++) for (int j = 1; j <= c; j++) std::cin >> a[i][j];
    for (int i = 1; i <= r; i++) for (int j = 1; j <= c; j++) std::cin >> b[i][j];
    for (int i = 1; i <= r; i++) for (int j = 1; j <= c; j++) if (b[i][j] == 'L') graph::addEdge(0, id(i, j, 0), 1), l++;
    for (int i = 1; i <= r; i++) for (int j = 1; j <= c; j++) if (a[i][j] != '0') graph::addEdge(id(i, j, 0), id(i, j, 1), a[i][j] - '0');
    for (int i = 1; i <= r; i++) for (int j = 1; j <= c; j++) for (int ii = i - d; ii <= i + d; ii++) for (int jj = j - d; jj <= j + d; jj++) if (check(i, j, ii, jj)) graph::addEdge(id(i, j, 1), id(ii, jj, 0), maxL);
    for (int i = 1; i <= r; i++) for (int j = 1; j <= d; j++) graph::addEdge(id(i, j, 1), 2 * r * c + 1, maxL);
    for (int i = 1; i <= r; i++) for (int j = 1; j <= d; j++) graph::addEdge(id(i, c - j + 1, 1), 2 * r * c + 1, maxL);
    for (int i = 1; i <= c; i++) for (int j = 1; j <= d; j++) graph::addEdge(id(j, i, 1), 2 * r * c + 1, maxL);
    for (int i = 1; i <= c; i++) for (int j = 1; j <= d; j++) graph::addEdge(id(r - j + 1, i, 1), 2 * r * c + 1, maxL);
    std::cout << l - graph::Dinic(0, 2 * r * c + 1) << '\n';
    return 0;
}