#include <cstdio>

const int maxN = 1e7;
const int maxM = 1e3;

int N, M;
int A[maxM + 10], B[maxM + 10];
int vis[maxM + 10];
int ans;

void Float(int l, int r, int now, int last) {
    if (l > r) return;
    if (vis[now]) return;
    while (last <= M && (l > B[last] || r < A[last])) last++;
    if (last > M) vis[now] = true, ans++;
    if (l <= A[last] && A[last] <= r) Float(l, A[last] - 1, now, last + 1);
    if (l <= B[last] && B[last] <= r) Float(B[last] + 1, r, now, last + 1);
    return;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= M; i++) scanf("%d%d", &A[i], &B[i]);
    for (int i = M; i >= 1; i--) Float(A[i], B[i], i, i + 1);
    printf("%d\n", ans);
    return 0;
}