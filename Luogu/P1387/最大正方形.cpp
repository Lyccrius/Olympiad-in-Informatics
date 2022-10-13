#include <bits/stdc++.h>

const int maxn = 100 + 10;

int n, m;
int matrix[maxn][maxn];

int prefix[maxn][maxn];

int main() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &matrix[i][j]);

            prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1]
                         - prefix[i - 1][j - 1] + matrix[i][j];
        }
    }

    int ans = 0;

    for (int len = 0; len < std::max(n, m); len++) {
        for (int i = len + 1; i <= n; i++) {
            for (int j = len + 1; j <= m; j++) {
                int total = prefix[i][j] + prefix[i - len][j - len]
                          - prefix[i - len][j] - prefix[i][j - len];
                
                if (total == len * len) {
                    ans = std::max(ans, len);
                }
            }
        }
    }

    printf("%d\n", ans);

    return 0;
}