#include <iostream>
#include <algorithm>
#include <vector>

typedef long long lxl;
typedef std::vector<int> vic;

const int maxN = 1500;
const lxl inf = 1e18;

int n, x;
int s, t;
int y[maxN + 10];
int z[maxN + 10];
int w[2 * maxN + 10];
lxl f[2 * maxN + 10][2 * maxN + 10][2];
lxl ans = inf;
vic raw;

int main() {
    std::cin >> n >> x;
    for (int i = 1; i <= n; i++) std::cin >> y[i];
    for (int i = 1; i <= n; i++) std::cin >> z[i];
    for (int i = 1; i <= n; i++) raw.push_back(y[i]);
    for (int i = 1; i <= n; i++) raw.push_back(z[i]);
    raw.push_back(0);
    raw.push_back(x);
    std::sort(raw.begin(), raw.end());
    raw.erase(std::unique(raw.begin(), raw.end()), raw.end());
    for (int i = 1; i <= n; i++) y[i] = std::lower_bound(raw.begin(), raw.end(), y[i]) - raw.begin();
    for (int i = 1; i <= n; i++) z[i] = std::lower_bound(raw.begin(), raw.end(), z[i]) - raw.begin();
    for (int i = 1; i <= n; i++) w[y[i]] = i;
    //for (int i = 1; i <= n; i++) printf("y[%d] = %d\n", i, y[i]);
    //for (int i = 0; i < raw.size(); i++) printf("%d: %d\n", i, w[i]);
    s = std::lower_bound(raw.begin(), raw.end(), 0) - raw.begin();
    t = std::lower_bound(raw.begin(), raw.end(), x) - raw.begin();
    std::fill(f[0][0], f[0][0] + sizeof(f) / 8, inf);
    f[s][s][0] = 0;
    f[s][s][1] = 0;
    for (int len = 2; len <= raw.size(); len++) {
        for (int i = 0; i < raw.size(); i++) {
            int j = i + len - 1;
            if (j >= raw.size()) break;
            if (!w[i] || (w[i] && i + 1 <= z[w[i]] && z[w[i]] <= j)) {
                //printf("[%d, %d] to l, %d: %d\n", i + 1, j, w[i], z[w[i]]);
                f[i][j][0] = std::min(f[i + 1][j][0] + raw[i + 1] - raw[i], f[i + 1][j][1] + raw[j] - raw[i]);
            }
            if (!w[j] || (w[j] && i <= z[w[j]] && z[w[j]] <= j - 1)) {
                //printf("[%d, %d] to r, %d: %d\n", i, j - 1, w[j], z[w[j]]);
                f[i][j][1] = std::min(f[i][j - 1][0] + raw[j] - raw[i], f[i][j - 1][1] + raw[j] - raw[j - 1]);
            }
            //printf("f[%d][%d] = %d, %d\n", i, j, f[i][j][0], f[i][j][1]);
        }
    }
    for (int i = 0; i < raw.size(); i++) {
        for (int j = i; j < raw.size(); j++) {
            //printf("f[%d][%d] = %d, %d\n", i, j, f[i][j][0], f[i][j][1]);
        }
    }
    for (int i = 0; i <= t; i++) {
        for (int j = t; j < raw.size(); j++) {
            //printf("f[%d][%d] = %d, %d\n", i, j, f[i][j][0], f[i][j][1]);
            ans = std::min(ans, f[i][j][0]);
            ans = std::min(ans, f[i][j][1]);
        }
    }
    if (ans == inf) {
        ans = -1;
    }
    std::cout << ans << '\n';
    return 0;
}