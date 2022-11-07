#include <cstdio>
#include <cmath>

int m;
int n;

int main() {
    scanf("%d", &m);
    while (m--) {
        scanf("%d", &n);
        int ans = std::ceil((double)n / 2);
        printf("%d\n", ans);
        for (int l = 1, r = n * 3; l < r; l += 3, r -= 3) printf("%d %d\n", l, r);
    }
    return 0;
}