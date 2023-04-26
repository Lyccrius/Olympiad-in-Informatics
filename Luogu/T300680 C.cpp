#include <iostream>
#include <cstdio>

const int maxN = 1000;
const int maxK = 1000;

int n, k;
int a[maxN + 10][maxN + 10];
int b[maxN + 10][maxN + 10];
int tot;
bool found;
int lx, ly;
int rx, ry;

bool check(int x, int y) {
    return b[x][y] - b[x - k][y] - b[x][y - k] + b[x - k][y - k] == 0;
}

bool cross() {
    return (lx <= rx) && (ly <= ry);
}

int main() {
    lx = 0;
    ly = 0;
    rx = maxN + 10;
    ry = maxN + 10;
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%1d", &a[i][j]);
            tot += a[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            b[i][j] = b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1] + a[i][j];
        }
    }
    for (int i = k; i <= n; i++) {
        for (int j = k; j <= n; j++) {
            if (check(i, j)) {
                found = true;
                lx = std::max(lx, i - k + 1);
                ly = std::max(ly, j - k + 1);
                rx = std::min(rx, i);
                ry = std::min(ry, j);
            }
        }
    }
    if (!found) {
        std::cout << "yc" << '\n';
        return 0;
    }
    if (cross()) {
        std::cout << "rx" << '\n';
        return 0;
    }
    if (tot & 1) {
        std::cout << "rx" << '\n';
    } else {
        std::cout << "yc" << '\n';
    }
    return 0;
}