#include <iostream>
#include <map>

typedef std::map<int, int> mii;

const int maxN = 1e6;
const int inf = 1e9 + 10;

int n;
int a[maxN + 10];
mii f[maxN + 10];

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) for (int j = -1; j <= 1; j++) f[i][j] = inf;
    f[1][a[1]] = 0;
    for (int i = 2; i <= n; i++) {
        if (a[i] == -1) {
            f[i][-1] = f[i - 1][-1];
            f[i][1] = f[i - 1][1] + 2;
            if (a[i - 1] == 1) {
                f[i][0] = std::min(f[i][0], f[i - 1][-1] + 1);
                f[i][0] = std::min(f[i][0], f[i - 1][0] + 1);
            }
        } else if (a[i] == 0) {
            f[i][-1] = f[i - 1][-1] + 1;
            f[i][0] = std::min(f[i - 1][-1], f[i - 1][0]);
            f[i][1] = f[i - 1][1] + 1;
            if (a[i - 1] == 1) {
                f[i][1] = std::min(f[i][1], f[i - 1][-1] + 1);
                f[i][1] = std::min(f[i][1], f[i - 1][0] + 1);
            }
        } else if (a[i] == 1) {
            f[i][-1] = f[i - 1][-1] + 2;
            f[i][0] = f[i - 1][-1] + 1;
            f[i][1] = std::min(f[i - 1][-1], std::min(f[i - 1][0], f[i - 1][1]));
            if (a[i - 1] == -1) {
                f[i][0] = std::min(f[i][0], f[i - 1][0] + 1);
            }
        }
    }
    int ans = inf;
    for (int i = -1; i <= 1; i++) ans = std::min(ans, f[n][i]);
    if (ans >= inf) {
        std::cout << "BRAK" << '\n';
    } else {
        std::cout << ans << '\n';
    }
    return 0;
}