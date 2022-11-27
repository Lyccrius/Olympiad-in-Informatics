#include <cstdio>
#include <cmath>
#include <algorithm>

const int maxN = 100 + 10;

int N;
int a[maxN];
int f[maxN][maxN];

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) scanf("%d", &a[i]), f[i][i] = a[i];
	for (int i = 1; i <= N; i++) for (int j = i + 1; j <= N; j++) f[i][j] = (j - i + 1) * std::abs(a[j] - a[i]);
	for (int len = 1; len <= N; len++) for (int i = 1; i <= N - len + 1; i++) {
		int j = i + len - 1;
		for (int k = i; k < j; k++) f[i][j] = std::max(f[i][j], f[i][k] + f[k + 1][j]);
	}
	printf("%d\n", f[1][N]);
	return 0;
}