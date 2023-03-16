#include <iostream>
#include <algorithm>
#include <vector>

typedef std::vector<int> vic;

const int maxN = 100;
const int maxM = 1e6;
const int inf = 1e9;

int n;
int a[maxN + 10][maxN + 10];
int m;
int p[maxM + 10];
int d[maxN + 10][maxN + 10];
int v[maxN + 10];
int last;
vic k;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) scanf("%1d", &a[i][j]);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) if (a[i][j]) d[i][j] = 1; else d[i][j] = inf;
    for (int i = 1; i <= n; i++) d[i][i] = 0;
    std::cin >> m;
    for (int i = 1; i <= m; i++) std::cin >> p[i];
    for (int i = 1; i <= m; i++) v[p[i]] = true;
    for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
    k.push_back(p[1]); last = 1;
    for (int i = 2; i <= m; i++) {
        if (d[p[last]][p[i]] != i - last) {
            k.push_back(p[i - 1]);
            last = i - 1;
        }
    }
    k.push_back(p[m]);
    std::cout << k.size() << '\n';
    for (auto v : k) std::cout << v << ' ';
    return 0;
}