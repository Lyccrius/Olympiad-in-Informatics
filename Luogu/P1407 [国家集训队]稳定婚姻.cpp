#include <iostream>
#include <string>
#include <map>

typedef std::string str;
typedef std::map<str, int> msi;

const int maxN = 4000;
const int maxM = 20000;

int n;
str a[maxN + 10], b[maxN + 10];
msi s;
int c;
int m;

int get(str t) {
    if (s[t]) return s[t];
    return s[t] = ++c;
}

namespace graph {
    struct Vertex {
        int vis;
        int head;
        int match;
    } vertex[2 * maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxN + maxM + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void init() {
        for (int i = 1; i <= c; i++) vertex[i].vis = false;
        return;
    }

    bool KM(int u) {
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (vertex[v].vis) continue;
            vertex[v].vis = true;
            if (vertex[v].match == 0 || KM(vertex[v].match)) {
                return true;
            }
        }
        return false;
    }
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i] >> b[i];
        graph::vertex[get(b[i])].match = get(a[i]);
    }
    std::cin >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> a[0] >> b[0];
        graph::addEdge(get(a[0]), get(b[0]));
    }
    for (int i = 1; i <= n; i++) {
        graph::vertex[get(b[i])].match = 0;
        graph::init();
        if (graph::KM(get(a[i]))) {
            std::cout << "Unsafe" << '\n';
        } else {
            std::cout << "Safe" << '\n';
        }
        graph::vertex[get(b[i])].match = get(a[i]);
    }
    return 0;
}