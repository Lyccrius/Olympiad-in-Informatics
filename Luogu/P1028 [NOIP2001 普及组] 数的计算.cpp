#include <cstdio>

const int maxN = 1e3 + 10;

int n;
int F[maxN];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		F[i] = 1;
		for (int j = 1; j <= i / 2; j++) F[i] += F[j];
	}
	printf("%d\n", F[n]);
	return 0;
}