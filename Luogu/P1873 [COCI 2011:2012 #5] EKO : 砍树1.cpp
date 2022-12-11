#include <cstdio>

const int maxN = 1e6 + 10;
const int maxM = 2e9 + 10;

int N, M;
int H[maxN];

bool check(int x) {
    long long res = 0;
    for (int i = 1; i <= N; i++) if (H[i] > x) res += H[i] - x;
    return res >= M;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) scanf("%d", &H[i]);
    int l = 0;
    int r = maxM;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    printf("%d\n", l);
    return 0;
}