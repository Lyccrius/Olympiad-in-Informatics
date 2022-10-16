#include <cstdio>

const int maxn = 5;

void solve() {
    int n, x;
    scanf("%d%d", &n, &x);
    int a[maxn];
    bool different = false;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        if (i && a[i] != a[0]) {
            different = true;
        }
    }

    // a[] 中存在不同元素
    if (different) {
        printf("Yes\n");
        return;
    }

    // a[] 中所有元素相同

    // x, a[] 同号
    if (x * a[0] > 0) {
        printf("Yes\n");
        return;
    }

    // x 不是 a[] 的倍数
    if (x % a[0] ^ 0) {
        printf("Yes\n");
        return;
    }

    printf("No\n");
    return;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }

    return 0;
}