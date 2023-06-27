#include <iostream>

const int maxN = 1e5;
const int maxM = 1e5;
const int maxQ = 1e5;

int n, m;
int a[maxN + 10];
int b[maxM + 10];
int a1[maxN + 10];
int an[maxN + 10];
int b1[maxM + 10];
int bm[maxM + 10];
int q;
int xs, ys, xe, ye;

void mian() {
    int ans = 0;
    std::cin >> xs >> ys >> xe >> ye;
    if (xs > xe) std::swap(xs, xe);
    if (ys > ye) std::swap(ys, ye);
    std::cout << std::min(a1[xe] - a1[xs], a1[xs] + an[xe] + (a[1] != a[n])) + std::min(b1[ye] - b1[ys], b1[ys] + bm[ye] + (b[1] != b[m])) << '\n';
    return;
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= m; i++) std::cin >> b[i];
    for (int i = 2; i <= n; i++) a1[i] = a1[i - 1] + (a[i] != a[i - 1]);
    for (int i = 2; i <= m; i++) b1[i] = b1[i - 1] + (b[i] != b[i - 1]);
    for (int i = n - 1; i >= 1; i--) an[i] = an[i + 1] + (a[i] != a[i + 1]);
    for (int i = m - 1; i >= 1; i--) bm[i] = bm[i + 1] + (b[i] != b[i + 1]);
    std::cin >> q;
    while (q--) mian();
    return 0;
}