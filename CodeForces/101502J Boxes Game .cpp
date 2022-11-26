#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxN = 1e3 + 10;

int T;
int n;
int a[maxN];
int vis[maxN][maxN];
int num[maxN][maxN];
int pre[maxN];

int A(int, int);
int B(int ,int);

int A(int l, int r) {
    if (l == r) return a[l];
    if (vis[l][r]) return num[l][r];
    int res = std::max(a[l] + B(l + 1, r), a[r] + B(l, r - 1));
    vis[l][r] = true;
    num[l][r] = res;
    return res;
}

int B(int l, int r) {
    return pre[r] - pre[l - 1] - A(l, r);
}

int main() {
    scanf("%d", &T);
    while (T--) {
        std::memset(vis, 0, sizeof(vis));
        std::memset(num, 0, sizeof(num));
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + a[i];
        printf("%d\n", A(1, n) - B(1, n));
    }
    return 0;
}