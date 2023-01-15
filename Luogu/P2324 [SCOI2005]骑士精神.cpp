#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

int T;

char res[10][10];
char mat[10][10];
int dx[10] = {0, 1, 1, -1, -1, 2, 2, -2, -2};
int dy[10] = {0, 2, -2, 2, -2, 1, -1, 1, -1};
int sx;
int sy;
int step;
bool ok;

void init() {
    ok = false;
    return;
}

int h() {
    int ret = 0;
    for (int i = 1; i <= 5; i++) for (int j = 1; j <= 5; j++) if (mat[i][j] != res[i][j]) ret++;
    //printf("%d\n", ret);
    return ret;
}

void DFS(int now, int x, int y) {
    if (now == step) {
        if (h() == 0) ok = true;
        return;
    }
    /*
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) std::cout << mat[i][j];
        std::cout << "\n";
    }
    std::cout << h();
    std::cout << "\n";
    */
    for (int i = 1; i <= 8; i++) {
        int xx = x + dx[i];
        int yy = y + dy[i];
        if (xx < 1 || xx > 5) continue;
        if (yy < 1 || yy > 5) continue;
        std::swap(mat[x][y], mat[xx][yy]);
        if (now + h() <= step) DFS(now + 1, xx, yy);
        std::swap(mat[x][y], mat[xx][yy]);
    }
    return;
}

void mian() {
    init();
    for (int i = 1; i <= 5; i++) for (int j = 1; j <= 5; j++) if (i <= j) res[i][j] = '1'; else res[i][j] = '0'; res[3][3] = '*'; res[4][4] = '0'; res[5][5] = '0';
    for (int i = 1; i <= 5; i++) for (int j = 1; j <= 5; j++) scanf(" %c", &mat[i][j]);
    for (int i = 1; i <= 5; i++) for (int j = 1; j <= 5; j++) if (mat[i][j] == '*') sx = i, sy = j;
    for (step = 0; step <= 15; step++) {
        DFS(0, sx, sy);
        if (ok) {
            std::cout << step << "\n";
            return;
        }
    }
    std::cout << -1 << "\n";
    return;
}

int main() {
    promote();
    scanf("%d", &T);
    while (T--) mian();
    return 0;
}