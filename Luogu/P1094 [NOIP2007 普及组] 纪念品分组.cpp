#include <cstdio>
#include <algorithm>

const int maxN = 3e4 + 10;

int w;
int n;
int P[maxN];

int main() {
	scanf("%d", &w);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &P[i]);
	std::sort(P + 1, P + n + 1);
	int l = 1;
	int r = n;
	int ans = 0;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (P[l] + P[r] <= w) {
			l++;
			r--;
			ans++;
		} else {
			r--;
			ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}