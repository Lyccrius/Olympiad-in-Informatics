#include <iostream>
#include <algorithm>
#include <vector>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef std::vector<int> vic;

const int maxN = 5e4;
const int maxM = 5e4 - 1;
const int inf = 1e9 + 10;

int n, m;
int a[maxN + 10], b[maxN + 10], l[maxN + 10];

namespace graph {
    struct Vertex {
        int head;
        int deg;
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
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        vertex[tail].deg++;
        return;
    }
}

namespace SubTask {
    namespace A { // m = 1
        bool is() {
            return m == 1;
        }

        int link[maxN + 10];
        int diam[maxN + 10];

        void DFS(int u, int from) {
            using namespace graph;
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                int w = edge[e].weight;
                if (v == from) continue;
                DFS(v, u);
                diam[u] = std::max(diam[u], diam[v]);
                diam[u] = std::max(diam[u], link[v] + w + link[u]);
                link[u] = std::max(link[u], link[v] + w);
            }
            return;
        }

        void mian() {
            DFS(1, 0);
            std::cout << diam[1];
            return;
        }
    }

    namespace B { // flower
        bool is() {
            for (int i = 1; i < n; i++) {
                if (a[i] != 1) {
                    return false;
                }
            }
            return true;
        }

        bool check(int x) {
            int i = 1;
            int j = n - 1;
            int cnt = 0;
            while (j >= 1 && l[j] >= x) {
                cnt++;
                j--;
            }
            while (i < j) {
                while (i < j && l[i] + l[j] < x) i++;
                if (i < j && l[i] + l[j] >= x) cnt++, i++, j--;
                else break;
            }
            return cnt >= m;
        }

        void mian() {
            std::sort(l + 1, l + n);
            /*
            int l = 0;
            int r = inf;
            while (l < r) {
                int mid = (l + r + 1) / 2;
                if (check(mid)) l = mid;
                else r = mid - 1;
            }
            std::cout << l;
            */
            int ans = 0;
            for (int i = 30; i >= 0; i--) {
                if (check(ans | (1 << i))) {
                    ans |= (1 << i);
                }
            }
            std::cout << ans;
            return;
        }
    }

    namespace C {
        bool is() {
            for (int i = 1; i < n; i++) {
                if (b[i] != a[i] + 1) {
                    return false;
                }
            }
            return true;
        }

        vic l;

        void DFS(int u, int from) {
            using namespace graph;
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                int w = edge[e].weight;
                if (v == from) continue;
                l.push_back(w);
                DFS(v, u);
            }
            return;
        }

        bool check(int x) {
            int cnt = 0;
            int now = 0;
            for (int i = 0; i < l.size(); i++) {
                now += l[i];
                if (now >= x) {
                    now = 0;
                    cnt++;
                }
            }
            return cnt >= m;
        }

        void mian() {
            DFS(1, 0);
            int l = 0;
            int r = inf;
            while (l < r) {
                int mid = (l + r + 1) / 2;
                if (check(mid)) l = mid;
                else r = mid - 1;
            }
            std::cout << l;
            return;
        }
    }
}

int main() {
    //freopen("track.in", "r", stdin);
    //freopen("track.out", "w", stdout);
    promote();
    std::cin >> n >> m;
    for (int i = 1; i < n; i++) {
        std::cin >> a[i] >> b[i] >> l[i];
        graph::addEdge(a[i], b[i], l[i]);
        graph::addEdge(b[i], a[i], l[i]);
    }
    if (SubTask::A::is()) SubTask::A::mian();
    else if (SubTask::B::is()) SubTask::B::mian();
    else SubTask::C::mian();
}