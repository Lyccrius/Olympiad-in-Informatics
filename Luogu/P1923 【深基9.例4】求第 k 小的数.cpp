#include <cstdio>
#include <algorithm>

const int maxN = 5e6 + 10;

int n, k;
int a[maxN];

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	std::sort(a + 1, a + n + 1);
	printf("%d\n", a[k + 1]);
	return 0;
}