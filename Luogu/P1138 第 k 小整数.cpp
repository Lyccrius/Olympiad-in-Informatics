#include <bits/stdc++.h>

const int maxn = 1e5 + 10;

int n, k;
int line[maxn];

int main() {
    scanf("%d%d", &n, &k);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &line[i]);
    }

    std::sort(line + 1, line + 1 + n);

    int cnt = 0;

    for (int i = 1; i <= n; i++) {
        if (line[i] != line[i - 1]) {
            cnt++;
        }

        if (cnt == k) {
            printf("%d\n", line[i]);
            return 0;
        }
    }

    printf("NO RESULT\n");

    return 0;
}