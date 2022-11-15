#include <cstdio>
#include <algorithm>

const int maxN = 1000 + 10;

int K;
int M, N;
int city[maxN][maxN];

int up[maxN][maxN];
int left[maxN][maxN];
int right[maxN][maxN];

int main() {
    scanf("%d", &K);
    for (int kase = 1; kase <= K; kase++) {
        scanf("%d%d", &M, &N);
        for (int i = 1; i <= M; i++) for (int j = 1; j <= N; j++) {
            char ch;
            scanf(" %c", &ch);
            while (ch != 'F' && ch != 'R') scanf(" %c", &ch);
            if (ch == 'F') city[i][j] = 0;
            else city[i][j] = 1;
        }
        int ans = 0;
        for (int i = 1; i <= M; i++) {
            int lo = 0;
            int ro = N + 1;
            for (int j = 1; j <= N; j++) if (city[i][j]) {
                up[i][j] = 0;
                left[i][j] = 0;
                lo = j;
            } else if (i == 1) {
                up[i][j] = 1;
                left[i][j] = lo + 1;
            } else {
                up[i][j] = up[i - 1][j] + 1;
                left[i][j] = std::max(left[i - 1][j], lo + 1);
            }
            for (int j = N; j >= 1; j--) if (city[i][j]) {
                right[i][j] = N;
                ro = j;
            } else if (i == 1) {
                right[i][j] = ro - 1;
                ans = std::max(ans, up[i][j] * (right[i][j] - left[i][j] + 1));
            } else {
                right[i][j] = std::min(right[i - 1][j], ro - 1);
                ans = std::max(ans, up[i][j] * (right[i][j] - left[i][j] + 1));
            }
        }
        printf("%d\n", ans * 3);
    }
    return 0;
}