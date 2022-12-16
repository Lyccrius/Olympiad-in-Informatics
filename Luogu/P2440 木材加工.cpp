#include <cstdio>
#include <algorithm>

const int maxN = 1e5 + 10;

int n, k;
int L[maxN];

bool check(int l) {
    int cnt = 0;
    for (int i = 1; i <= n; i++) cnt += L[i] / l;
    return cnt >= k;
}

int main() {
    scanf("%d%d", &n, &k);
    int maxL = 0;
    for (int i = 1; i <= n; i++) scanf("%d", &L[i]), maxL = std::max(maxL, L[i]);
    int l = 0;
    int r = maxL;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    printf("%d\n", l);
    return 0;
}