#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const int maxN = 2e5;
const int maxQ = 2e5;

int n, q, s, t;
int a[maxN + 10];
lxl b[maxN + 10];
int l, r, x;
lxl ans;

lxl delta(lxl x) {
    if (x > 0) return - x * s;
    if (x < 0) return - x * t;
    return 0;
}

void add(int pos, int val) {
    if (pos > n) return;
    //printf("add(%d, %d)\n", pos, val);
    ans -= delta(b[pos]);
    //printf("- %d\n", delta(b[pos]));
    b[pos] += val;
    ans += delta(b[pos]);
    //printf("+ %d\n", delta(b[pos]));
    return;
}

int main() {
    promote();
    std::cin >> n >> q >> s >> t;
    for (int i = 0; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) b[i] = a[i] - a[i - 1];
    for (int i = 1; i <= n; i++) ans += delta(b[i]);//, printf("*%d\n", ans);
    for (int i = 1; i <= q; i++) {
        std::cin >> l >> r >> x;
        add(l, x);
        add(r + 1, - x);
        std::cout << ans << '\n';
    }
    return 0;
}