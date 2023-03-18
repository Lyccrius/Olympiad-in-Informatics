#include <iostream>
#include <algorithm>
#include <vector>

typedef long long lxl;
typedef std::vector<int> vic;

const int maxN = 3e5;
const int maxM = 3e5;
const int inf = 1e9 + 10;

int n, m;
int a[maxN + 10];
int b[maxN + 10];
int l, r;
int res;
lxl ans;

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) b[i] = inf;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            b[i] = std::min(b[i], std::abs(a[i] - a[j]));
            b[j] = std::min(b[j], std::abs(a[i] - a[j]));
        }
    }
    for (int i = 1; i <= m; i++) {
        std::cin >> l >> r; res = 0;
        for (int j = l; j <= r; j++) {
            for (int k = j + 1; k <= r; k++) {
                if (std::abs(a[j] - a[k]) == b[j]) res++;
                if (std::abs(a[j] - a[k]) == b[k]) res++;
            }
        }
        ans += 1ll * res * i;
    }
    std::cout << ans;
    return 0;
}