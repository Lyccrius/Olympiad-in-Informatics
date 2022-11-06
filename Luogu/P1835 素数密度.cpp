#include <cstdio>
#include <cstring>
#include <cmath>

const int maxn = 1e6 + 10;
const int inf = 1e9 + 10;

long long l, r;

int minPrimeFactor[maxn];
int prime[maxn];
int cnt;

int composite[maxn];
long long ansPrime[maxn];
int ansCnt;

void primes(int n) {
    std::memset(minPrimeFactor, 0, sizeof(minPrimeFactor));
    cnt = 0;
    for (int i = 2; i <= n; i++) {
        if (minPrimeFactor[i] == 0) {
            minPrimeFactor[i] = i;
            prime[++cnt] = i;
        }
        for (int j = 1; j <= cnt; j++) {
            if (prime[j] > minPrimeFactor[i] ||
                prime[j] > n / i) break;
            minPrimeFactor[i * prime[j]] = prime[j];
        }
    }
    return;
}

int main() {
    primes(maxn);
    scanf("%lld%lld", &l, &r);
    int sqrtR = std::sqrt(r);
    if (l == 1) composite[0] = true;
    for (int i = 1; i <= cnt; i++) {
        for (long long j = std::ceil((double)l / prime[i]); j * prime[i] <= r; j++) {
            if (j > 1) composite[j * prime[i] - l] = true;
        }
    }
    for (long long i = l; i <= r; i++) {
        if (!composite[i - l]) {
            ansCnt++;
            ansPrime[ansCnt] = i;
        }
    }
    printf("%d\n", ansCnt);
    return 0;
}