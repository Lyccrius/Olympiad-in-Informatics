#include <cstdio>

int n;
long long res = 1;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) res *= i;
	printf("%lld\n", res);
	return 0;
}