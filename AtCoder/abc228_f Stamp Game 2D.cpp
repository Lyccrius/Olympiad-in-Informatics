#include <iostream>
#include <deque>

typedef long long lxl;
typedef std::deque<int> diq;

const int maxH = 1000;
const int maxW = 1000;

int h, w, h1, w1, h2, w2;
lxl a[maxH + 10][maxW + 10];
lxl b[maxH + 10][maxW + 10];
lxl c[maxH + 10][maxW + 10];
lxl d[maxH + 10][maxW + 10];
lxl e[maxH + 10][maxW + 10];
lxl f[maxH + 10][maxW + 10];
lxl ans;

int main() {
    std::cin >> h >> w >> h1 >> w1 >> h2 >> w2;
    h2 = std::min(h1, h2);
    w2 = std::min(w1, w2);
    for (int i = 1; i <= h; i++) for (int j = 1; j <= w; j++) std::cin >> a[i][j];
    for (int i = 1; i <= h; i++) for (int j = 1; j <= w; j++) b[i][j] = b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1] + a[i][j];
    for (int i = 1; i + h1 - 1 <= h; i++) for (int j = 1; j + w1 - 1 <= w; j++) c[i][j] = b[i + h1 - 1][j + w1 - 1] - b[i - 1][j + w1 - 1] - b[i + h1 - 1][j - 1] + b[i - 1][j - 1];
    for (int i = 1; i + h2 - 1 <= h; i++) for (int j = 1; j + w2 - 1 <= w; j++) d[i][j] = b[i + h2 - 1][j + w2 - 1] - b[i - 1][j + w2 - 1] - b[i + h2 - 1][j - 1] + b[i - 1][j - 1];
    for (int i = 1; i <= h; i++) {
        diq q;
        for (int j = w; j >= 1; j--) {
            while (q.size() && q.front() - j > w1 - w2) q.pop_front();
            while (q.size() && d[i][q.back()] <= d[i][j]) q.pop_back();
            q.push_back(j);
            if (q.size()) e[i][j] = d[i][q.front()];
        }
    }
    for (int j = 1; j <= w; j++) {
        diq q;
        for (int i = h; i >= 1; i--) {
            while (q.size() && q.front() - i > h1 - h2) q.pop_front();
            while (q.size() && e[q.back()][j] <= e[i][j]) q.pop_back();
            q.push_back(i);
            if (q.size()) f[i][j] = e[q.front()][j];
        }
    }
    for (int i = 1; i + h1 - 1 <= h; i++) for (int j = 1; j + w1 - 1 <= w; j++) ans = std::max(ans, c[i][j] - f[i][j]);
    std::cout << ans << '\n';
    return 0;
}