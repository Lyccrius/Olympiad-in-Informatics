#include <cstdio>
#include <algorithm>

const int maxN = 300 + 10;

int n;
int h[maxN];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &h[i]);
	std::sort(h + 1, h + n + 1);
	int h2[maxN];
	int l = 1;
	int r = n;
	int head = 0;
	while (l <= r) {
		head++;
		if (head & 1) {
			h2[head] = h[r];
			r--;
		} else {
			h2[head] = h[l];
			l++;
		}
	}
	h2[0] = 0;
	long long ans = 0;
	for (int i = 1; i <= n; i++) ans += (long long)(h2[i] - h2[i - 1]) * (h2[i] - h2[i - 1]);
	printf("%lld\n", ans);
	return 0;
}