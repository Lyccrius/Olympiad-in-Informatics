#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>

const int maxN = 20 + 10;
const int maxX = 5e6 + 10;

int n, k;
int x[maxN];
int isPrime[maxX];

bool check(long long a) {
    if (a < maxX && isPrime[a] != -1) return isPrime[a];
    for (int i = 2; i * i <= a; i++) {
        if (a % i == 0) return isPrime[a] = 0;
    }
    return isPrime[a] = 1;
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", &x[i]);
    std::memset(isPrime, -1, sizeof(isPrime));
    isPrime[1] = 0;
    isPrime[2] = 1;
    isPrime[3] = 1;
    int last = 0;
    long long ans = 0;;
    for (int i = 0; i < (1 << n); i++) {
        int ii = i;
        int cnt = 0;
        int tot = 0;
        long long sum = 0;
        while (ii) {
            tot++;
            if (ii & 1) {
                cnt++;
                sum += x[tot];
            }
            ii >>= 1;
        }
        if (cnt != k) continue;
        if (check(sum)) ans++;
    }
    printf("%lld\n", ans);
    return 0;
}