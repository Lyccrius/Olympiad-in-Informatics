#include <cstdio>
#include <algorithm>

const int maxn = 1e5 + 10;

int t;
int n;
int a[maxn];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        std::sort(a + 2, a + n + 1);
        if (a[1] > a[2]) printf("Alice\n");
        else printf("Bob\n");
    }
    return 0;
}