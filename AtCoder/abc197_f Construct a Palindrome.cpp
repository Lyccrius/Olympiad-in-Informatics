#include <iostream>
#include <vector>
#include <deque>

typedef char chr;
typedef std::pair<int, int> pii;
typedef std::vector<pii> vpc;
typedef std::deque<pii> dpq;

const int maxN = 1000;
const int maxM = 1000;
const int inf = 1e9 + 10;

int n, m;
int u, v;
chr ch;
int ans = inf;

int a[maxN + 10][maxN + 10];
vpc b[maxN + 10];
vpc c[maxN + 10][maxN + 10];
int d[maxN + 10][maxN + 10];

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> u >> v >> ch;
        a[u][v] = true;
        a[v][u] = true;
        b[u].push_back(std::make_pair(v, ch - 'a' + 1));
        b[v].push_back(std::make_pair(u, ch - 'a' + 1));
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (auto ei : b[i]) {
                for (auto ej : b[j]) {
                    if (ei.second == ej.second) {
                        c[i][j].push_back(std::make_pair(ei.first, ej.first));
                    }
                }
            }
        }
    }
    dpq q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            d[i][j] = inf;
        }
    }
    d[1][n] = 0;
    q.push_back(std::make_pair(1, n));
    while (!q.empty()) {
        int u = q.front().first;
        int v = q.front().second;
        q.pop_front();
        for (auto e : c[u][v]) {
            int x = e.first;
            int y = e.second;
            if (d[x][y] == inf) {
                d[x][y] = d[u][v] + 1;
                q.push_back(std::make_pair(x, y));
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        ans = std::min(ans, d[i][i] * 2);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j]) {
                ans = std::min(ans, d[i][j] * 2 + 1);
            }
        }
    }
    if (ans == inf) ans = -1;
    std::cout << ans << '\n';
    return 0;
}