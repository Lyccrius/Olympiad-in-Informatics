#include <bits/stdc++.h>

int T;

int a, b;
int n;

int f[5];

using namespace std;

int main() {
    scanf("%d", &T);

    while (T--) {
        scanf("%d%d%d", &a, &b, &n);

        n %= 3;

        f[0] = a;
        f[1] = b;
        f[2] = a ^ b;

        printf("%d\n", f[n]);
    }

    return 0;
}