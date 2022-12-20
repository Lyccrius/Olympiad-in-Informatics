#include <cstdio>
#include <cmath>
#include <algorithm>

const int maxN = 2e5 + 10;
const int inf = 1e9 + 10;

int t;
int n;
int a[maxN];
int d[maxN];

void mian() {
	scanf("%d", &n);
	unsigned long long dif = 1;
	int l = 0;
	int r = inf;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) d[i] = a[i] - a[i - 1];
	for (int i = 2; i <= n; i++) {
		int cx = std::ceil((a[i - 1] + a[i]) / 2.0);
		int fx = std::floor((a[i - 1] + a[i]) / 2.0);
		if (d[i] > 0) {
			r = std::min(r, fx);
		}
		if (d[i] < 0) {
			l = std::max(l, cx);
		}
	}
	if (l <= r) printf("%d\n", l);
	else printf("%d\n", -1);
	return;
}

int main() {
	scanf("%d", &t);
	while (t--) mian();
	return 0;
}