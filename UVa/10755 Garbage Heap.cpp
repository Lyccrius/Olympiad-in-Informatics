#include <cstdio>
#include <cstring>
#include <algorithm>

const long long inf = 1LL << 60;
const int maxN = 20 + 10;

int T;

long long S[maxN][maxN][maxN];

void expand(int i, int& b0, int& b1, int& b2) {
    b0 = i & 1; i >>= 1;
    b1 = i & 1; i >>= 1;
    b2 = i & 1;
    return;
}

int sign(int b0, int b1, int b2) {
    if ((b0 + b1 + b2) % 2) return 1;
    return -1;
}

long long sum(int x1, int x2, int y1, int y2, int z1, int z2) {
    int dx = x2 - x1 + 1;
    int dy = y2 - y1 + 1;
    int dz = z2 - z1 + 1;
    long long s = 0;
    for (int i = 0; i < 8; i++) {
        int b0, b1, b2;
        expand(i, b0, b1, b2);
        s -= S[x2 - b0 * dx][y2 - b1 * dy][z2 - b2 * dz] * sign(b0, b1, b2);
    }
    return s;
}

int main() {
    scanf("%d", &T);
    for (int kase = 1; kase <= T; kase++) {
        int A, B, C;
        int b0, b1, b2;
        scanf("%d%d%d", &A, &B, &C);
        std::memset(S, 0, sizeof(S));
        for (int x = 1; x <= A; x++) for (int y = 1; y <= B; y++) for (int z = 1; z <= C; z++) scanf("%lld", &S[x][y][z]);
        for (int x = 1; x <= A; x++) for (int y = 1; y <= B; y++) for (int z = 1; z <= C; z++) for (int i = 1; i <= 7; i++) {
            expand(i, b0, b1, b2);
            S[x][y][z] += S[x - b0][y - b1][z - b2] * sign(b0, b1, b2);
        }
        long long ans = -inf;
        for (int x1 = 1; x1 <= A; x1++) for (int x2 = x1; x2 <= A; x2++) for (int y1 = 1; y1 <= B; y1++) for (int y2 = y1; y2 <= B; y2++) {
            long long M = 0;
            for (int z = 1; z <= C; z++) {
                long long s = sum(x1, x2, y1, y2, 1, z);
                ans = std::max(ans, s - M);
                M = std::min(M, s);
            }
        }
        printf("%lld\n", ans);
        if (kase != T) printf("\n");
    }
    return 0;
}