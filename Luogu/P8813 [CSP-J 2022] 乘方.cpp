#include <cstdio>

const int mod = 1e9;

int a, b;

int pow(long long a, long long b) {
    long long ans = 1;
    if (a == 1) return 1;
    if (a == mod && b != 1) return -1;
    while (b) {
        if (b & 1) {
            ans = ans * a;
            if (ans > mod || ans < 0) {
                return -1;
            }
        }
        a *= a;
        b >>= 1;
    }
    return ans;
}

int main() {
    scanf("%d%d", &a, &b);
    int ans = pow(a, b);
    printf("%d\n", ans);
    return 0;
}