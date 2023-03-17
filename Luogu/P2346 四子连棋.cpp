#include <iostream>

typedef char chr;

const int maxN = 4;
const int maxM = 4;
const int dx[5] = {0, 0, 1, 0, - 1};
const int dy[5] = {0, 1, 0, - 1, 0};

int n = 4;
int m = 4;
chr a[maxN + 10][maxM + 10];
chr b[maxN + 10][maxM + 10];
int x1, y1, x2, y2;
int lim;
int sol;

void init() {
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) b[i][j] = a[i][j];
    return;
}

bool check() {
    if (b[1][1] == b[2][2] && b[2][2] == b[3][3] && b[3][3] == b[4][4]) return true;
    if (b[1][4] == b[2][3] && b[2][3] == b[3][2] && b[3][2] == b[4][1]) return true;
    for (int i = 1; i <= n; i++) if (b[i][1] == b[i][2] && b[i][2] == b[i][3] && b[i][3] == b[i][4]) return true;
    for (int j = 1; j <= m; j++) if (b[1][j] == b[2][j] && b[2][j] == b[3][j] && b[3][j] == b[4][j]) return true;
    return false;
}

void DFS(int cur, int now, int x1, int y1, int x2, int y2) {
    if (now == lim) {
        if (check()) {
            sol = true;
        }
        return;
    }
    if (cur) {
        for (int i = 1; i <= 4; i++) {
            int x_ = x1 + dx[i];
            int y_ = y1 + dy[i];
            if (x_ < 1 || x_ > n) continue;
            if (y_ < 1 || y_ > m) continue;
            if (b[x_][y_] == 'B') continue;
            std::swap(b[x1][y1], b[x_][y_]);
            DFS(cur ^ 1, now + 1, x_, y_, x2, y2);
            std::swap(b[x1][y1], b[x_][y_]);
        }
        for (int i = 1; i <= 4; i++) {
            int x_ = x2 + dx[i];
            int y_ = y2 + dy[i];
            if (x_ < 1 || x_ > n) continue;
            if (y_ < 1 || y_ > m) continue;
            if (b[x_][y_] == 'B') continue;
            std::swap(b[x2][y2], b[x_][y_]);
            DFS(cur ^ 1, now + 1, x1, y1, x_, y_);
            std::swap(b[x2][y2], b[x_][y_]);
        }
    } else {
        for (int i = 1; i <= 4; i++) {
            int x_ = x1 + dx[i];
            int y_ = y1 + dy[i];
            if (x_ < 1 || x_ > n) continue;
            if (y_ < 1 || y_ > m) continue;
            if (b[x_][y_] == 'W') continue;
            std::swap(b[x1][y1], b[x_][y_]);
            DFS(cur ^ 1, now + 1, x_, y_, x2, y2);
            std::swap(b[x1][y1], b[x_][y_]);
        }
        for (int i = 1; i <= 4; i++) {
            int x_ = x2 + dx[i];
            int y_ = y2 + dy[i];
            if (x_ < 1 || x_ > n) continue;
            if (y_ < 1 || y_ > m) continue;
            if (b[x_][y_] == 'W') continue;
            std::swap(b[x2][y2], b[x_][y_]);
            DFS(cur ^ 1, now + 1, x1, y1, x_, y_);
            std::swap(b[x2][y2], b[x_][y_]);
        }
    }
    return;
}

int main() {
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) std::cin >> a[i][j];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) if (a[i][j] == 'O') {if (!x1) x1 = i, y1 = j; else x2 = i, y2 = j;}
    while (!sol) {
        init(); DFS(0, 0, x1, y1, x2, y2);
        init(); DFS(1, 0, x1, y1, x2, y2);
        lim++;
    }
    std::cout << lim - 1;
    return 0;
}