#include <cstdio>

int T;
long long n;

int main() {
	 scanf("%d", &T);
	 while (T--) {
		scanf("%lld", &n);
		long long res = n * (n - 1);
		if (!res) res = 1;
		printf("%lld\n", res);
	 }
	 return 0;
}