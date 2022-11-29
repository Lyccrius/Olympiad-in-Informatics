#include <cstdio>
#include <algorithm>

const int maxN = 2000 + 10;
const int maxP = 1e6 + 10;
const int inf = 1e9 + 10;

int N;
int x[maxN], y[maxN];
int farm[maxN][maxN];
long long pre[maxN][maxN];
int range[maxP];
int head = 0;
int tot;
long long ans = inf;

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%d%d", &x[i], &y[i]), range[++head] = x[i], range[++head] = y[i];
    std::sort(range + 1, range + head + 1);
    tot = std::unique(range + 1, range + head + 1) - range - 1;
    for (int i = 1; i <= N; i++) {
        int X = std::lower_bound(range + 1, range + tot + 1, x[i]) - range;
        int Y = std::lower_bound(range + 1, range + tot + 1, y[i]) - range;
        farm[X][Y]++;
    }
    for (int i = 1; i <= tot; i++) for (int j = 1; j <= tot; j++) pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + farm[i][j];
    for (int i = 1; i <= tot; i++) for (int j = 1; j <= tot; j++) ans = std::min(ans, std::max(std::max(pre[i][j], pre[tot][tot] - pre[i][tot] - pre[tot][j] + pre[i][j]), std::max(pre[i][tot] - pre[i][j], pre[tot][j] - pre[i][j])));
    printf("%lld\n", ans);
    return 0;
}