#include <iostream>

typedef long long lxl;

const int maxH = 1000;
const int maxW = 1000;

int h, w, h1, w1, h2, w2;
lxl a[maxH + 10][maxW + 10];
lxl b[maxH + 10][maxW + 10];
lxl c[maxH + 10][maxW + 10];
lxl d[maxH + 10][maxW + 10];
lxl ans;

int main() {
    std::cin >> h >> w >> h1 >> w1 >> h2 >> w2;
    h2 = std::min(h1, h2);
    w2 = std::min(w1, w2);
    for (int i = 1; i <= h; i++) for (int j = 1; j <= w; j++) std::cin >> a[i][j];
    for (int i = 1; i <= h; i++) for (int j = 1; j <= w; j++) b[i][j] = b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1] + a[i][j];
    for (int i = 1; i + h1 - 1 <= h; i++) for (int j = 1; j + w1 - 1 <= w; j++) c[i][j] = b[i + h1 - 1][j + w1 - 1] - b[i - 1][j + w1 - 1] - b[i + h1 - 1][j - 1] + b[i - 1][j - 1];
    for (int i = 1; i + h2 - 1 <= h; i++) for (int j = 1; j + w2 - 1 <= w; j++) d[i][j] = b[i + h2 - 1][j + w2 - 1] - b[i - 1][j + w2 - 1] - b[i + h2 - 1][j - 1] + b[i - 1][j - 1];
    for (int i = 1; i + h1 - 1 <= h; i++) for (int j = 1; j + w1 - 1 <= w; j++) for (int k = 1; k <= h1 - h2; k++) d[i][j] = std::max(d[i][j], d[i + k][j]);
    for (int i = 1; i + h1 - 1 <= h; i++) for (int j = 1; j + w1 - 1 <= w; j++) for (int k = 1; k <= w1 - w2; k++) d[i][j] = std::max(d[i][j], d[i][j + k]);
    for (int i = 1; i + h1 - 1 <= h; i++) for (int j = 1; j + w1 - 1 <= w; j++) ans = std::max(ans, c[i][j] - d[i][j]);
    /*
    for (int i = 1; i + h1 - 1 <= h; i++) {
        for (int j = 1; j + w1 - 1 <= w; j++) {
            printf("%4d", d[i][j]);
        }
        printf("\n");
    }
    */
    std::cout << ans << '\n';
    return 0;
}