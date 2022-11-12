#include <cstdio>
#include <cstring>

#define front 1
#define left 2
#define back 3
#define right 4
#define top 5
#define bottom 6

const int maxn = 10 + 10;

int n;

char pos[maxn][maxn][maxn];
char view[10][maxn][maxn];

void translate(int k, int i, int j, int p, int &x, int &y, int &z) {
    switch(k) {
        case front: {
            x = p;
            y = j;
            z = i;
            break;
        }
        case left: {
            x = n - j + 1;
            y = p;
            z = i;
            break;
        }
        case back: {
            x = n - p + 1;
            y = n - j + 1;
            z = i;
            break;
        }
        case right: {
            x = j;
            y = n - p + 1;
            z = i;
            break;
        }
        case top: {
            x = n - i + 1;
            y = j;
            z = p;
            break;
        }
        case bottom: {
            x = i;
            y = j;
            z = n - p + 1;
            break;
        }
    }
    return;
}

int main() {
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 1; i <= n; i++) {
            for (int k = 1; k <= 6; k++) {
                for (int j = 1; j <= n; j++) {
                    scanf(" %c", &view[k][i][j]);
                }
            }
        }
        std::memset(pos, '#', sizeof(pos));
        for (int k = 1; k <= 6; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    if (view[k][i][j] == '.') {
                        for (int p = 1; p <= n; p++) {
                            int x, y, z;
                            translate(k, i, j, p, x, y, z);
                            pos[x][y][z] = '.';
                        }
                    }
                }
            }
        }
        bool deleted = true;
        while (deleted) {
            deleted = false;
            for (int k = 1; k <= 6; k++) {
                for (int i = 1; i <= n; i++) {
                    for (int j = 1; j <= n; j++) {
                        if (view[k][i][j] != '.') {
                            for (int p = 1; p <= n; p++) {
                                int x, y, z;
                                translate(k, i, j, p, x, y, z);
                                if (pos[x][y][z] == '.') continue;
                                if (pos[x][y][z] == '#') {
                                    pos[x][y][z] = view[k][i][j];
                                    break;
                                }
                                if (pos[x][y][z] == view[k][i][j]) break;
                                pos[x][y][z] = '.';
                                deleted = true;
                            }
                        }
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                for (int k = 1; k <= n; k++) {
                    if (pos[i][j][k] != '.') ans++;
                }
            }
        }
        printf("Maximum weight: %d gram(x)\n", ans);
    }
    return 0;
}