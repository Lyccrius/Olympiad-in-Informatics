#include <iostream>
#include <algorithm>

typedef long long lxl;

const int maxN = 2000;
const int inf = 1e9 + 10;

lxl N, x;
lxl a[maxN + 10];
lxl b[maxN + 10][maxN + 10];
lxl ans = 1ll * maxN * inf;

int main() {
    std::cin >> N >> x;
    for (int i = 1; i <= N; i++) std::cin >> a[i];
    for (int i = 1; i <= N; i++) b[0][i] = a[i];
    for (int i = 1; i <= N; i++) {
        b[i - 1][0] = b[i - 1][N];
        for (int j = 1; j <= N; j++) {
            b[i][j] = std::min(b[i - 1][j - 1], a[j]);
            //printf("b[%d][%d] = %d\n", i, j, b[i][j]);
        }
        //printf("\n");
    }
    for (int i = 0; i <= N; i++) {
        lxl res = x * i;
        for (int j = 1; j <= N; j++) res += b[i][j];
        ans = std::min(ans, res);
    }
    std::cout << ans;
    return 0;
}