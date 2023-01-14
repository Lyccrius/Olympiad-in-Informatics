#include <cstdio>
#include <algorithm>

const int maxN = 50;

int t;

int n;
int a[maxN + 10];

void mian() {
    bool dif = false;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 2; i <= n; i++) if (a[i] != a[i - 1]) dif = true;
    if (dif == false) {
        printf("NO\n");
        return;
    }
    printf("YES\n");
    std::sort(a + 1, a + n + 1);
    printf("%d ", a[1]);
    for (int i = n; i >= 2; i--) printf("%d ", a[i]);
    printf("\n");
    return;
}

int main() {
    scanf("%d", &t);
    while (t--) mian();
    return 0;
}