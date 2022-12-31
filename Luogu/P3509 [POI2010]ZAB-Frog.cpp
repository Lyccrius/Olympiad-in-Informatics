#include <cstdio>
#include <cmath>

const int maxN = 1e6;
const int logM = 59;

long long n, k, m;
long long a[maxN + 10];
long long next[maxN + 10][logM + 10];

long long lowbit(long x) {
    return x & -x;
}

int main() {
    scanf("%lld%lld%lld", &n, &k, &m);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    int l = 1;
    int r = k + 1;
	for (int i = 1; i <= n; i++) {
		while (r + 1 <= n && a[r + 1] - a[i] < a[i] - a[l]) l++, r++;
		if (a[r] - a[i] > a[i] - a[l]) next[i][0] = r;
		else next[i][0] = l;
	}
    for (int p = 1; p <= logM; p++) for (int i = 1; i <= n; i++) next[i][p] = next[next[i][p - 1]][p - 1];
    for (int i = 1; i <= n; i++) {
        long long res = i;
        long long t = m;
        while (t) {
            res = next[res][(int)std::log2(lowbit(t))];
            t -= lowbit(t);
        }
        printf("%lld ", res);
    }
	return 0;
}