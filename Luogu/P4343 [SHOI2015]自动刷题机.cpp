#include <cstdio>
#include <algorithm>

const long long inf = 1e18 + 10;
const int maxL = 1e5 + 10;

int l, k;
int x[maxL];

int AC(long long n) {
	int res = 0;
	long long sum = 0;
	for (int i = 1; i <= l; i++) {
		sum = std::max(sum + x[i], (long long)0);
		if (sum >= n) {
			sum = 0;
			res++;
		}
	}
	return res;
}

int main() {
	scanf("%d%d", &l, &k);
	for (int i = 1; i <= l; i++) scanf("%d", &x[i]);
	long long minN = -1;
	long long maxN = -1;
	long long L = 1;
	long long R = inf;
	while (L <= R) {
		long long mid = (L + R) >> 1;
		if (AC(mid) <= k) {
			R = mid - 1;
			if (AC(mid) == k) minN = mid;
		}
		else L = mid + 1;
	}
	L = 1;
	R = inf;
	while (L <= R) {
		long long mid = (L + R) >> 1;
		if (AC(mid) >= k) {
			L = mid + 1;
			if (AC(mid) == k) maxN = mid;
		}
		else R = mid - 1;
	}
	if (minN == -1) printf("-1\n");
	else printf("%lld %lld\n", minN, maxN);
	return 0;
}