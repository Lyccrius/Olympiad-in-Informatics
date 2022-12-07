#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxN = 1e3 + 10;
const int maxM = 1e3 + 10;

int n, m;
int a[maxN][maxM];
long long f[maxN];
long long dw[maxN];
long long up[maxN];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
	for (int i = 1; i <= n; i++) f[i] = f[i - 1] + a[i][1];
	for (int j = 2; j < m; j++) {
		std::memset(dw, 0, sizeof(dw));
		std::memset(up, 0, sizeof(up));
		dw[1] = f[1] + a[1][j];
		up[n] = f[n] + a[n][j];
		for (int i = 2; i <= n; i++) dw[i] = std::max(f[i], dw[i - 1]) + a[i][j];
		for (int i = n - 1; i >= 1; i--) up[i] = std::max(f[i], up[i + 1]) + a[i][j];
		for (int i = 1; i <= n; i++) f[i] = std::max(dw[i], up[i]);
	}
	for (int i = 1; i <= n; i++) f[i] = std::max(f[i], f[i - 1]) + a[i][m];
	printf("%lld", f[n]);
	return 0;
}