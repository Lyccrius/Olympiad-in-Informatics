#include <cstdio>

const int maxR = 500;
const int maxC = 500;

int R, C, A, B;
int N[maxR + 10][maxC + 10];
int P[maxR + 10][maxC + 10];

bool check(int x) {
    int cntR = 0;
    int lastR = 0;
    for (int i = 1; i <= R; i++) {
        int cntC = 0;
        int lastC = 0;
        for (int j = 1; j <= C; j++) if (P[i][j] - P[i][lastC] - P[lastR][j] + P[lastR][lastC] >= x) { cntC++; lastC = j; }
        if (cntC >= B) { cntR++; lastR = i; }
    }
    if (cntR >= A) return true;
    return false;
}

int main() {
    scanf("%d%d%d%d", &R, &C, &A, &B);
    for (int i = 1; i <= R; i++) for (int j = 1; j <= C; j++) scanf("%d", &N[i][j]);
    for (int i = 1; i <= R; i++) for (int j = 1; j <= C; j++) P[i][j] = P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1] + N[i][j];
    int l = 0;
    int r = P[R][C];
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    printf("%d\n", l);
    return 0;
}