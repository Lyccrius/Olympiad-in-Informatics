#include <cstdio>

int t;

int main() {
    scanf("%d", &t);
    while (t--) {
        int cnt = 0;
        int a[5][5];
        for (int i = 1; i <= 2; i++) for (int j = 1; j <= 2; j++) scanf("%d", &a[i][j]), cnt += a[i][j];
        if (cnt) printf("%d\n", 1 + cnt / 4);
        else printf("0\n");
    }
    return 0;
}