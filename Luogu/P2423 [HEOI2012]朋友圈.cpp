#include <iostream>

const int maxT = 6;
const int maxA = 200;
const int maxB = 3000;

int T;
int A, B, M;
int a[maxA + 10];
int b[maxB + 10];
int x, y;
int ab[maxA + 10][maxB + 10];

int popcount(int x) {
    int ret = 0;
    while (x) {
        if (x & 1) ret++;
        x = x / 2;
    }
    return ret;
}

namespace graph {
    struct Vertex {
        int match;
        int head;
        int vis;
        int on;
    } vertex[maxB + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxB * maxB + 10];

    int ecnt;
    int time;
    
    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void init() {
        for (int i = 1; i <= A; i++) for (int j = 1; j <= B; j++) ab[i][j] = false;
        for (int i = 1; i <= B; i++) vertex[i].head = 0;
        for (int i = 1; i <= B; i++) vertex[i].vis = 0;
        ecnt = 0;
        time = 0;
        return;
    }

    void build() {
        for (int i = 1; i <= B; i++) {
            if ((b[i] & 1) == 0) continue;
            for (int j = 1; j <= B; j++) {
                if ((b[j] & 1) == 1) continue;
                if ((popcount(b[i] | b[j]) & 1) == 1) continue;
                addEdge(i, j);
            }
        }
        return;
    }

    bool DFS(int u) {
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (vertex[v].on == false) continue;
            if (vertex[v].vis == time) continue;
            vertex[v].vis = time;
            if (vertex[v].match == 0 || DFS(vertex[v].match)) {
                vertex[v].match = u;
                return true;
            }
        }
        return false;
    }

    void clear() {
        for (int i = 1; i <= B; i++) vertex[i].match = false;
        for (int i = 1; i <= B; i++) vertex[i].on = false;
        return;
    }

    int solve0() {
        int ret = 0;
        clear();
        for (int i = 1; i <= B; i++) vertex[i].on = true;
        for (int i = 1; i <= B; i++) {
            time++;
            if ((b[i] & 1) == 0) continue;
            if (DFS(i)) ret++;
        }
        return B - ret;
    }

    int solve1() {
        int ret = 0;
        for (int i = 1; i <= A; i++) {
            int tot = 0;
            int res = 0;
            clear();
            for (int j = 1; j <= B; j++) if (ab[i][j]) vertex[j].on = true, tot++;
            for (int j = 1; j <= B; j++) {
                time++;
                if ((b[j] & 1) == 0) continue;
                if (vertex[j].on == false) continue;
                if (DFS(j)) res++;
            }
            ret = std::max(ret, tot - res + 1);
        }
        return ret;
    }

    int solve2() {
        int ret = 0;
        for (int i = 1; i <= A; i++) {
            for (int j = i + 1; j <= A; j++) {
                if (((a[i] ^ a[j]) & 1) == 0) continue;
                int tot = 0;
                int res = 0;
                clear();
                for (int k = 1; k <= B; k++) if (ab[i][k] && ab[j][k]) vertex[k].on = true, tot++;
                for (int k = 1; k <= B; k++) {
                    time++;
                    if ((b[k] & 1) == 0) continue;
                    if (vertex[k].on == false) continue;
                    if (DFS(k)) res++;
                }
                ret = std::max(ret, tot - res + 2);
            }
        }
        return ret;
    }
}

void mian() {
    graph::init();
    std::cin >> A >> B >> M;
    for (int i = 1; i <= A; i++) std::cin >> a[i];
    for (int i = 1; i <= B; i++) std::cin >> b[i];
    for (int i = 1; i <= M; i++) std::cin >> x >> y, ab[x][y] = true;
    graph::build();
    int ans = 0;
    ans = std::max(ans, graph::solve0());
    ans = std::max(ans, graph::solve1());
    ans = std::max(ans, graph::solve2());
    std::cout << ans << '\n';
    return;
}

int main() {
    std::cin >> T;
    while (T--) mian();
    return 0;
}