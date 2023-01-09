#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxN = 200;
const int maxM = 20000;
const int maxQ = 50000;

int N, M;
int T[maxN + 10];
int i, j, w;
int Q;
int x, y, t;

int f[maxN + 10][maxN + 10][maxN + 10];

int main() {
    std::memset(f, 0x3f, sizeof(f));
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) scanf("%d", &T[i]);
    for (int i = 0; i < N; i++) f[0][i][i] = 0;
    while (M--) scanf("%d%d%d", &i, &j, &w), f[0][i][j] = w, f[0][j][i] = w;
    for (int i = 1; i < N; i++) {
        for (int j = 1; j <= N; j++) {
            f[0][i][j] = std::min(f[0][i][j], f[0][i][0] + f[0][0][j]);
        }
    }
    for (int k = 1; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                f[k][i][j] = std::min(f[k - 1][i][j], f[k - 1][i][k] + f[k - 1][k][j]);
            }
        }
    }
    scanf("%d", &Q);
    while (Q--) {
        scanf("%d%d%d", &x, &y, &t);
        int p = std::upper_bound(T, T + N, t) - T - 1;
        if (t < T[x] || t < T[y] || f[p][x][y] == 0x3f3f3f3f) {
            printf("%d\n", -1);
        } else {
            printf("%d\n", f[p][x][y]);
        }
    }
    return 0;
}