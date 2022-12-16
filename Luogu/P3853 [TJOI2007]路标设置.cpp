#include <cstdio>
#include <algorithm>

const int maxN = 1e5 + 10;

int L, N, K;
int pos[maxN];
int dif[maxN];

bool check(int x) {
    int cnt = 0;
    for (int i = 2; i <= N; i++) {
        if (dif[i] >= x) cnt += dif[i] / x;
        if (dif[i] % x == 0) cnt--;
    }
    return cnt <= K;
}

int main() {
    scanf("%d%d%d", &L, &N, &K);
    for (int i = 1; i <= N; i++) scanf("%d", &pos[i]), dif[i] = pos[i] - pos[i - 1];
    int l = 0;
    int r = L;
    int res;
    while (l + 1< r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid;
        else l = mid;
    }
    printf("%d\n", r);
    return 0;
}