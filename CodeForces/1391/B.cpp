#include <bits/stdc++.h>

const int maxn = 100 + 10;

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, m;
        scanf("%d%d", &n, &m);
        char matrix[maxn][maxn];
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                scanf(" %c", &matrix[i][j]);
            }
        }

        int ans = 0;
        for (int i = 1; i < m; i++) {
            if (matrix[n][i] == 'D') {
                ans++;
            }
        }
        for (int i = 1; i < n; i++) {
            if (matrix[i][m] == 'R') {
                ans++;
            }
        }

        printf("%d\n", ans);
    }

    return 0;
}