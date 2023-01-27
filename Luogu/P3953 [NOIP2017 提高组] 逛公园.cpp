#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1e5;
const int maxM = 2e5;
const int maxK = 50;
const int inf = 1e9;

int T;
int N, M, K, P;
int a[maxM + 10], b[maxM + 10], c[maxM + 10];

struct Graph {
    struct Vertex {
        int vertex;
        int head;
        int vis;
        int dis;
        int ins;
        int low;
        int dfn;
        int bel;

        bool operator<(const Vertex &other) const {
            return dis > other.dis;
        }
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        int weight;
    } edge[maxM + 10];

    int ecnt;
    
    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].weight = weight;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void Dijkstra(int s) {
        std::priority_queue<Vertex> q;
        vertex[s].dis = 0;
        q.push(vertex[s]);
        while (!q.empty()) {
            int u = q.top().vertex;
            q.pop();
            if (vertex[u].vis) continue;
            vertex[u].vis = true;
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                int w = edge[e].weight;
                if (vertex[v].dis > vertex[u].dis + w) {
                    vertex[v].dis = vertex[u].dis + w;
                    q.push(vertex[v]);
                }
            }
        }
        return;
    }

    int dfn;
    std::stack<int> s;

    void addSCC(int u) {
        int v;
        int cnt = 0;
        do {
            v = s.top();
            s.pop();
            vertex[v].bel = true;
            vertex[v].ins = false;
            cnt++;
        } while (v != u);
        //printf("----------add %d, sum = %d\n", u, cnt);
        if (cnt == 1) vertex[v].bel = false;
        return;
    }

    void Tarjan(int u) {
        dfn++;
        vertex[u].low = dfn;
        vertex[u].dfn = dfn;
        vertex[u].ins = true;
        s.push(u);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (!vertex[v].dfn) {
                Tarjan(v);
                vertex[u].low = std::min(vertex[u].low, vertex[v].low);
            } else if (vertex[v].ins) {
                vertex[u].low = std::min(vertex[u].low, vertex[v].dfn);
            }
        }
        if (vertex[u].low == vertex[u].dfn) addSCC(u);
        //printf("Tarjan %d\n", u);
        //printf("dfn = %d, low = %d\n", vertex[u].dfn, vertex[u].low);
        return;
    }

    void init() {
        for (int i = 1; i <= maxN; i++) vertex[i].vertex = i;
        for (int i = 1; i <= maxN; i++) vertex[i].head = 0;
        for (int i = 1; i <= maxN; i++) vertex[i].vis = false;
        for (int i = 1; i <= maxN; i++) vertex[i].dis = inf;
        for (int i = 1; i <= maxN; i++) vertex[i].ins = false;
        for (int i = 1; i <= maxN; i++) vertex[i].low = 0;
        for (int i = 1; i <= maxN; i++) vertex[i].dfn = 0;
        for (int i = 1; i <= maxN; i++) vertex[i].bel = false;
        ecnt = 0;
        dfn = 0;
        while (!s.empty()) s.pop();
        return;
    }
};

Graph forward;
Graph reverse;
Graph zero;

int f[maxN + 10][maxK + 10];
int ans;

void init() {
    std::fill(f[0], f[0] + (maxN + 10) * (maxK + 10), -1);
    f[1][0] = 1;
    ans = 0;
    forward.init();
    reverse.init();
    zero.init();
    return;
}

int DFS(int u, int k) {
    if (f[u][k] != -1) {
        //printf("%d\n", f[u][k]);
        return f[u][k];
    }
    f[u][k] = 0;
    for (int e = reverse.vertex[u].head; e; e = reverse.edge[e].next) {
        int v = reverse.edge[e].head;
        int t = forward.vertex[u].dis - forward.vertex[v].dis + k - reverse.edge[e].weight;
        //printf("%d, %d\n", v, t);
        if (t < 0) continue;
        f[u][k] = (f[u][k] + DFS(v, t)) % P;
    }
    //printf("DFS(%d, %d) %d\n", u, k, f[u][k]);
    return f[u][k];
}

void mian() {
    init();
    std::cin >> N >> M >> K >> P;
    for (int i = 1; i <= M; i++) {
        std::cin >> a[i] >> b[i] >> c[i];
        forward.addEdge(a[i], b[i], c[i]);
        reverse.addEdge(b[i], a[i], c[i]);
        if (c[i] == 0) zero.addEdge(a[i], b[i], c[i]);
    }
    forward.Dijkstra(1);
    reverse.Dijkstra(N);
    for (int i = 1; i <= N; i++) {
        if (!zero.vertex[i].dfn) {
            zero.Tarjan(i);
        }
    }
    bool infinity = false;
    for (int i = 1; i <= N; i++) {
        //printf("%d: %d, %d, %d\n", i, zero.vertex[i].bel, forward.vertex[i].dis + reverse.vertex[i].dis, forward.vertex[N].dis + K);
        if (zero.vertex[i].bel && 
            forward.vertex[i].dis + reverse.vertex[i].dis <= 
            forward.vertex[N].dis + K) {
            //printf("%d###\n", i);
            infinity = true;
            break;
        }
    }
    if (infinity) {
        std::cout << -1;
    } else {
        for (int k = 0; k <= K; k++) ans = (ans + DFS(N, k)) % P;
        std::cout << ans;
        //printf("**");
    }
    std::cout << '\n';
    return;
}

int main() {
    promote();
    std::cin >> T;
    while (T--) mian();
    return 0;
}