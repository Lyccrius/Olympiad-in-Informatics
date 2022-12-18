#include <cstdio>
#include <cmath>
#include <algorithm>
 
const int maxN = 2e5 + 10;
 
int n;
long long a[maxN];
 
void mian() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	std::sort(a + 2, a + n + 1);
	for (int i = 2; i <= n; i++) if (a[i] > a[1]) a[1] += std::ceil(1.0 * (a[i] - a[1]) / 2);
	printf("%lld\n", a[1]);
	return;
}
 
int main() {
	int t;
	scanf("%d", &t);
	while (t--) mian();
	return 0;
}