#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn = 2e5 + 10;

int n, p, q;

int F[maxn][2];
int a[maxn];

int main() {
	scanf("%d%d%d", &n, &p, &q);

	if (p >= q) {
		printf("%d\n", q * n);
		return 0;
	}

	int t = q / p;
	for (int i = 1; i <= t; i++) {
		a[i] = p * i * i;
	}

	std::memset(F, 0x3f, sizeof(F));
	F[0][0] = 0;
	F[0][1] = 0;
	for (int i = 1; i <= n; i++) {
		F[i][1] = std::min(F[i][1], F[i - 1][0] + q);
		for (int j = 1; j <= t; j++) {
			if (i >= j) {
				F[i][0] = std::min(F[i][0], F[i - j][1] + a[j]);
			}
		}
	}

	printf("%d\n", std::min(F[n][1], F[n][0]));

	return 0;
}