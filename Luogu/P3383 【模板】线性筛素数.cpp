#include <cstdio>

const int maxn = 1e8 + 10;

int n, q;
int k;

int minPrimeFactor[maxn];
int prime[maxn];
int cnt;

void PreWork() {
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
    scanf("%d%d", &n, &q);
    PreWork();
    while (q--) {
        scanf("%d", &k);
        printf("%d\n", prime[k]);
    }
    return 0;
}