#include <iostream>
#include <algorithm>
#include <vector>

typedef char chr;
typedef std::vector<int> vic;

const int maxN = 100;
const int maxM = 100;
const int dx[5] = {0, -1, 0, 1, 0};
const int dy[5] = {0, 0, -1, 0, 1};

int n, m;
chr a[maxN + 10][maxM + 10];
int t;
int sum;
int cnt;
vic ans;

namespace graph {
    struct Vertex {
        int vis;
        int head;
        int match;
    } vertex[maxN * maxM + 10];

    struct Edge {
        int head;
        int next;
    } edge[4 * maxN * maxM + 10];

    int ecnt;

    void addEdge(int tail, int head) {
    printf("%d, %d\n", tail, head);
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    bool DFS1(int u, int t) {
        printf("DFS1(%d\n", u);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (vertex[v].vis == t) continue;
            vertex[v].vis = t;
            if (vertex[v].match == 0 || DFS1(vertex[v].match, t)) {
                vertex[v].match = u;
                vertex[u].match = v;
                printf("%d match %d\n", u, v);
                return true;
            }
        }
        return false;
    }

    void DFS2(int u, int t) {
        if (vertex[u].vis == t) return;
        vertex[u].vis = t;
        ans.push_back(u);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (!vertex[v].match) continue;
            DFS2(vertex[v].match, t);
        }
        return;
    }
}

int id(int i, int j) {
    return (i - 1) * m + j;
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) std::cin >> a[i][j];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) if (a[i][j] == '.')  sum++;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if ((i + j) & 1) continue;
            if (a[i][j] == '#') continue;
            for (int k = 1; k <= 4; k++) {
                int ii = i + dx[k];
                int jj = j + dy[k];
                if (ii < 1 || ii > n) continue;
                if (jj < 1 || jj > m) continue;
                if (a[ii][jj] == '#') continue;
                graph::addEdge(id(i, j), id(ii, jj));
                graph::addEdge(id(ii, jj), id(i, j));
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if ((i + j) & 1) continue;
            if (a[i][j] == '#') continue;
            if (graph::DFS1(id(i, j), ++t)) cnt++;
        }
    }
    if (2 * cnt == sum) {
        std::cout << "LOSE" << '\n';
        return 0;
    }
    t++;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == '#') continue;
            if (graph::vertex[id(i, j)].match) continue;
            graph::DFS2(id(i, j), t);
        }
    }
    std::cout << "WIN" << '\n';
    std::sort(ans.begin(), ans.end());
    for (auto i : ans) {
        std::cout << i / m + 1 << ' ' << i % m + 1 << '\n';
    }
    return 0;
}