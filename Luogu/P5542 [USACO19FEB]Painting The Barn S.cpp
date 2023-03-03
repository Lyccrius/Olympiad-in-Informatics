#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1000;

int n, k;
int x1, y1, x2, y2;
int a[maxN + 10][maxN + 10];
int ans;

int main() {
    promote();
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        std::cin >> x1 >> y1 >> x2 >> y2;
        a[x1 + 1][y1 + 1]++;
        a[x2 + 1][y2 + 1]++;
        a[x1 + 1][y2 + 1]--;
        a[x2 + 1][y1 + 1]--;
    }
    for (int i = 1; i <= maxN; i++) {
        for (int j = 1; j <= maxN; j++) {
            a[i][j] = a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1] + a[i][j];
            if (a[i][j] == k) ans++;
        }
    }
    std::cout << ans;
    return 0;
}