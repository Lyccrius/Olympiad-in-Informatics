#include <cstdio>

const int maxN = 2e6 + 10;

int n;
int a;

int main() {
    int mode = 0;
    int cnt = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a);
        if (cnt == 0) mode = a;
        if (mode == a) cnt++;
        if (mode != a) cnt--;
    }
    printf("%d\n", mode);
    return 0;
}