#include <iostream>
#include <algorithm>

typedef long long lxl;

const int maxN = 1e5;

lxl N, M, V, P;
lxl a[maxN + 10];
lxl p[maxN + 10];
lxl s[maxN + 10];
lxl ans;

bool check(int i) {
    if (a[i] + M < a[P]) return false;
    if (V - (P - 1) - 1 - (N - i) <= 0) return true;
    if (((V - (P - 1) - 1 - (N - i)) * M - p[i - 1] - 1) / (i - P) + 1 + a[P] <= a[i] + M) return true;
    return false;
}

int main() {
    std::cin >> N >> M >> V >> P;
    for (int i = 1; i <= N; i++) std::cin >> a[i];
    std::sort(a + 1, a + N + 1);
    std::reverse(a + 1, a + N + 1);
    ans = P;
    for (int i = P + 1; i <= N; i++) {
        p[i] = p[i - 1] + (a[P] - a[i]);
    }
    for (int i = N - 1; i >= 1; i--) {
        if (a[i] == a[i + 1]) {
            s[i] = s[i + 1];
        } else {
            s[i] = s[i + 1] + 1ll * (a[i] - a[i + 1]) * (N - i);
        }
    }
    for (int i = P + 1; i <= N; i++) {
        if (check(i)) {
            ans++;
        } else {
            break;
        }
    }
    std::cout << ans << '\n';
    return 0;
}