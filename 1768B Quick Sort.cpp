#include <cstdio>
#include <cmath>

const int maxN = 1e5;

int t;

int n, k;
int p[maxN + 10];

void mian() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", &p[i]);
    int head = 1;
    int cnt = n;
    for (int i = 1; i <= n; i++) if (p[i] == head) cnt--, head++;
    int ans = std::ceil(1.0 * cnt / k);
    printf("%d\n", ans);
    return;
}

int main() {
    scanf("%d", &t);
    while (t--) mian();
    return 0;
}