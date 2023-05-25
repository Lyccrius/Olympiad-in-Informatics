#include <iostream>
#include <deque>

typedef std::deque<int> diq;

const int maxN = 1000;

int t, kase;
int n;
int g[maxN + 10][maxN + 10];
int r[maxN + 10][maxN + 10];
int b[maxN + 10][maxN + 10];
int c[maxN + 10];
int mg[maxN + 10];
int mb[maxN + 10];

void mian() {
    if (kase - 1) std::cout << '\n';
    std::cin >> n;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) std::cin >> b[i][j];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) std::cin >> g[i][j];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) r[i][g[i][j]] = j;
    for (int i = 1; i <= n; i++) mg[i] = 0;
    for (int i = 1; i <= n; i++) mb[i] = 0;
    for (int i = 1; i <= n; i++) c[i] = 0;
    diq q;
    for (int i = 1; i <= n; i++) q.push_back(i);
    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        c[u]++;
        int girl = b[u][c[u]];
        int other = mg[girl];
        if (!other) {
            mg[girl] = u;
            mb[u] = girl;
            continue;
        }
        if (r[girl][u] < r[girl][other]) {
            mg[girl] = u;
            mb[u] = girl;
            q.push_back(other);
            continue;
        }
        q.push_back(u);
    }
    for (int i = 1; i <= n; i++) std::cout << mb[i] << '\n';
    return;
}

int main() {
    std::cin >> t;
    for (kase = 1; kase <= t; kase++) mian();
    return 0;
}