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

int closestDis;
long long closestLeft;
long long closestRight;
int mostDis;
long long mostLeft;
long long mostRight;

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
    while (scanf("%lld%lld", &l, &r) == 2 && l && r) {
        int sqrtR = std::sqrt(r);
        memset(composite, false, sizeof(composite));
        if (l == 1) composite[0] = true;
        for (int i = 1; i <= cnt; i++) {
            for (long long j = std::ceil((double)l / prime[i]); j * prime[i] <= r; j++) {
                if (j > 1) composite[j * prime[i] - l] = true;
            }
        }
        ansCnt = 0;
        closestDis = inf;
        mostDis = 0;
        for (long long i = l; i <= r; i++) {
            if (!composite[i - l]) {
                ansCnt++;
                ansPrime[ansCnt] = i;
            }
        }
        for (int i = 1; i < ansCnt; i++) {
            int dis = ansPrime[i + 1] - ansPrime[i];
            if (closestDis > dis) {
                closestDis = dis;
                closestLeft = ansPrime[i];
                closestRight = ansPrime[i + 1];
            }
            if (mostDis < dis) {
                mostDis = dis;
                mostLeft = ansPrime[i];
                mostRight = ansPrime[i + 1];
            }
        }
        if (mostDis) printf("%lld,%lld are closest, %lld,%lld are most distant.\n", closestLeft, closestRight, mostLeft, mostRight);
        else printf("There are no adjacent primes.\n");
    }
    return 0;
}