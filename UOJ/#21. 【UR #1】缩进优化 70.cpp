#include <iostream>
#include <algorithm>

typedef long long lxl;

const int maxN = 1e5;
const int maxA = 1e5;

int n;
int a[maxN + 10];
lxl b[maxA + 10];
int c[maxA + 10];
lxl sum;
lxl ans = 1ll * maxN * maxA;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) c[a[i]]++;
    for (int i = 1; i <= n; i++) sum += a[i];
    for (int ai = 1; ai <= maxA; ai++) {
        for (int l = 1, r; l <= ai; l = r + 1) {
            r = ai / (ai / l);
            b[l] += 1ll * c[ai] * (ai / l);
            b[r + 1] -= 1ll * c[ai] * (ai / l);
        }
    }
    for (int i = 1; i <= maxA; i++) b[i] += b[i - 1];
    for (int x = 1; x <= maxA; x++) ans = std::min(ans, sum - b[x] * (x - 1));
    std::cout << ans << '\n';
    return 0;
}