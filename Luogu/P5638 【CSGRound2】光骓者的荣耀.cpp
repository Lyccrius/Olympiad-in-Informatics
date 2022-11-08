#include <cstdio>
#include <algorithm>

const int maxn = 1e6 + 10;

int n, k;
long long a[maxn];

long long pre[maxn];

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i < n; i++) {
		scanf("%lld", &a[i]);
		pre[i] = pre[i - 1] + a[i];
	}
	long long save = 0;
	for (int i = 0; i + k < n; i++) save = std::max(save, pre[i + k] - pre[i]);
	printf("%lld\n", pre[n - 1] - save);
	return 0;
}