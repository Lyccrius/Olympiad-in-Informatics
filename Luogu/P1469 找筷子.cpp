#include <cstdio>

const int maxN = 1e7 + 10;

int n;
int a;
int ans;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a), ans ^= a;
	printf("%d\n", ans);
	return 0;
}