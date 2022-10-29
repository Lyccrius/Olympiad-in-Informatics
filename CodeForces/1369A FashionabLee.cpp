#include <cstdio>

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int n;
        scanf("%d", &n);
        if (n % 4) {
            printf("NO\n");
        } else {
            printf("YES\n");
        }
    }

    return 0;
}