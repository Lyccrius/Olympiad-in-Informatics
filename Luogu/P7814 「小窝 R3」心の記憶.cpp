#include <cstdio>

const int maxN = 1e6 + 10;
const int maxM = 1e6 + 10;

int T;
int n, m;
int A[maxN];


void mian() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%1d", &A[i]);
	if ((n == 1) || (n == m) || (n == 2 && A[1] ^ A[2])) {
		printf("%d\n", -1);
		return;
	}
	int kase = 1;
	for (int i = 1; i < n - 1; i++) if (A[i] ^ A[i + 1]) kase = 2;
	if (A[n] == A[n - 1]) kase = 2;
	if (kase == 1) {
		for (int i = 1; i < m; i++) {
			if (i == 1) {
				printf("%d", A[i]);
				printf("%d", !A[i]);
				continue;
			}
			if (i > n) {
				printf("%d", A[n]);
				continue;
			}
			printf("%d", A[i]);
		}
	} else {
		for (int i = 1; i < n; i++) printf("%d", A[i]);
		for (int i = n; i < m; i++) printf("%d", !A[n]);
		printf("%d", A[n]);
	}
	printf("\n");
	return;
}

int main() {
	scanf("%d", &T);
	while (T--) mian();
	return 0;
}