#include <cstdio>
#include <cmath>

const int maxN = 100 + 10;

int n;
int a[maxN];

bool isPrime(int x) {
	if (x <= 1) return false;
	for (int i = 2; i <= std::sqrt(x); i++) if (x % i == 0) return false;
	return true;
}

int main() {
	scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) if (isPrime(a[i])) printf("%d ", a[i]);
	return 0;
}