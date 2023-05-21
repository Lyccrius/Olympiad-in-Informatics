#include <iostream>
#include <map>

typedef long long lxl;
typedef std::pair<int, int> pii;
typedef std::map<lxl, bool> mmb;
typedef std::map<lxl, pii> mmp;

const int maxN = 10;
const int maxM = 10;
const int feifei = 0;
const int niuniu = 0;
const int inf = 1e9;

int n, m;
int a[maxN + 10][maxM + 10];
int b[maxN + 10][maxM + 10];
int h[maxM + 10];
mmb vis;
mmp tmp;

lxl hash() {
    lxl ret = 0;
    for (int i = 1; i <= m; i++) ret = ret * 11 + h[i];
    return ret;
}

pii DFS(int who, int cnt) {
    if (cnt == n * m) return std::make_pair(0, 0); 
    if (vis[hash()]) return tmp[hash()];
    vis[hash()] = true;
    pii ret = std::make_pair(-inf, inf);
    for (int i = 1; i <= m; i++) {
        if (h[i] == h[i - 1]) continue;
        int j = h[i] + 1;
        h[i]++;
        pii res = DFS(who ^ 1, cnt + 1);
        std::swap(res.first, res.second);
        if (who == feifei) res.first += a[j][i]; else res.first += b[j][i];
        if (ret.first - ret.second < res.first - res.second) ret = res;
        h[i]--;
    }
    return tmp[hash()] = ret;
}

int main() {
    std::cin >> n >> m; h[0] = n;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) std::cin >> a[i][j];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) std::cin >> b[i][j];
    pii ans = DFS(feifei, 0);
    std::cout << ans.first - ans.second << '\n';
    return 0;
}