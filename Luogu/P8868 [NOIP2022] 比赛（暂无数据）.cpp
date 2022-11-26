#include <cstdio>
#include <algorithm>

const int maxN = 2.5e5 + 10;
const int maxQ = 2.5e5 + 10;

int T, n;
int a[maxN];
int b[maxN];
int Q;
int l[maxQ], r[maxQ];

int main() {
	scanf("%d%d", &T, &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
	scanf("%d", &Q);
	for (int i = 1; i <= Q; i++) scanf("%d%d", &l[i], &r[i]);
	for (int i = 1; i <= Q; i++) {
		unsigned long long ans = 0;
		for (int p = l[i]; p <= r[i]; p++) for (int q = p; q <= r[i]; q++) {
			int ma = 0;
			int mb = 0;
			for (int j = l[i]; j <= r[i]; j++) {
				if (p <= j && j <= q) ma = std::max(ma, a[j]);
				if (p <= j && j <= q) mb = std::max(mb, b[j]);
			}
			if (!ma || !mb) break;
			ans += (unsigned long long) ma * mb;
			//printf("# p = %d, q = %d: ma = %d, mb = %d, ans = %llu\n", p, q, ma, mb, ans);
		}
		printf("%llu\n", ans);
	}
	return 0;
}