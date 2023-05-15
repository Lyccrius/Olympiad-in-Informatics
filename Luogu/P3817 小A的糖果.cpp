#include <cstdio>

typedef long long lxl;

const int maxN = 1e5;

int n, x;
int a[maxN + 10];
lxl res;

int main() {
    scanf("%d%d", &n, &x);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        int sum = a[i - 1] + a[i];
        if (sum > x) {
            int dif = sum - x;
            a[i] -= dif;
            res += dif;
        }
    }
    printf("%lld\n", res);
    return 0;
}