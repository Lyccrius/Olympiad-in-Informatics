#include <cstdio>
#include <cstring>

const int maxN = 2000;
const int maxM = 2000;
const int maxK = 170;

int n, m, k;
int a[maxK + 10];

char res[maxN + 10][maxM + 10];

int main() {
    std::memset(res, '.', sizeof(res));
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i <= k; i++) scanf("%d", &a[i]);
    for (int x = 0; x < n; x++) {
        int y = 0;
        int powX = 1;
        for (int i = 0; i <= k; i++) {
            y += powX * a[i];
            powX *= x;
        }
        if (x + 1 <= maxN && y + 1 <= maxM && x + 1 >= 0 && y + 1 >= 0) res[x + 1][y + 1] = '*';
    }
    for (int j = m; j >= 1; j--) {
        for (int i = 1; i <= n; i++) printf("%c", res[i][j]);
        printf("\n");
    }
    return 0;
}