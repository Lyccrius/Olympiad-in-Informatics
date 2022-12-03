#include <cstdio>

const int maxN = 100 + 10;

int n;
int a[maxN][maxN];
int b[maxN][maxN];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) scanf("%d", &a[i][j]);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) b[i][j] = a[i][j];
	for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) b[i][j] |= b[i][k] & b[k][j];
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) printf("%d ", b[i][j]);
		printf("\n");
	}
	return 0;
}