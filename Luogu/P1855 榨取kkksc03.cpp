#include <cstdio>
#include <algorithm>

const int maxN = 100 + 10;
const int maxM = 200 + 10;
const int maxT = 200 + 10;

int n, M, T;
int m[maxN];
int t[maxN];
int f[maxM][maxT];

int main() {
    scanf("%d%d%d", &n, &M, &T);
    for (int i = 1; i <= n; i++) scanf("%d%d", &m[i], &t[i]);
    for (int i = 1; i <= n; i++) {
        for (int j = M; j >= m[i]; j--) {
            for (int k = T; k >= t[i]; k--) {
                f[j][k] = std::max(f[j][k], f[j - m[i]][k - t[i]] + 1);
            }
        }
    }
    printf("%d\n", f[M][T]);
    return 0;
}