#include <cstdio>
#include <cstring>

const int maxn = 1e5 + 10;

int n;

int main() {
    scanf("%d", &n);
    printf("a");
    for (int i = 1; i < n; i++) printf("%c", (char)((i - 1) % 25 + 98));
    return 0;
}