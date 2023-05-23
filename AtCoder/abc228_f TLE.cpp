#include <iostream>

typedef long long lxl;

const int maxH = 1000;
const int maxW = 1000;
const lxl inf = 1e18;

int h, w, h1, w1, h2, w2;
lxl a[maxH + 10][maxW + 10];
lxl p[maxH + 10][maxW + 10];
lxl ans;

lxl calc(int h1, int w1, int h2, int w2) {
    h1 = std::max(h1, 1);
    w1 = std::max(w1, 1);
    h2 = std::min(h2, h);
    w2 = std::min(w2, w);
    return p[h2][w2] - p[h2][w1 - 1] - p[h1 - 1][w2] + p[h1 - 1][w1 - 1];
}

lxl A(int x, int y) {
    lxl tot = calc(x, y, x + h1 - 1, y + w1 - 1);
    lxl ret = calc(x, y, x + h1 - 1, y + w1 - 1);
    for (int i = x; i - h2 + 1 <= x; i++) for (int j = y; j - w2 + 1 <= y; j++) ret = std::min(ret, tot - calc(std::max(x, i - h2 + 1), std::max(y, j - w2 + 1), i, j));
    for (int i = x + h1 - 1; i + h2 - 1 >= x + h1 - 1; i--) for (int j = y + w1 - 1; j + w2 - 1 >= y + w1 - 1; j--) ret = std::min(ret, tot - calc(i, j, std::min(i + h2 - 1, x + h1 - 1), std::min(j + w2 - 1, y + w1 - 1)));
    for (int i = x; i + h2 - 1 <= x + h1 - 1; i++) for (int j = y; j + w2 - 1 <= y + w1 - 1; j++) ret = std::min(ret, tot - calc(i, j, i + h2 - 1, j + w2 - 1));
    return ret;
}

int main() {
    std::cin >> h >> w >> h1 >> w1 >> h2 >> w2;
    for (int i = 1; i <= h; i++) for (int j = 1; j <= w; j++) std::cin >> a[i][j];
    for (int i = 1; i <= h; i++) for (int j = 1; j <= w; j++) p[i][j] = p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1] + a[i][j];
    for (int i = 1; i + h1 - 1 <= h; i++) for (int j = 1; j + w1 - 1 <= w; j++) ans = std::max(ans, A(i, j));
    std::cout << ans << '\n';
    return 0;
}