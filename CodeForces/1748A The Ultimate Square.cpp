#include <cstdio>
 
int t;
int n;
 
int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        printf("%d\n", (n + 1) >> 1);
    }
    return 0;
}