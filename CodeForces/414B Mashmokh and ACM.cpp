#include <cstdio>

const int mod = 1e9 + 7;
const int maxN = 2000 + 10;
const int maxK = 2000 + 10;

int n, k;
long long f[maxN][maxK];
long long ans;

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i <= n; i++) f[1][i] = 1;
	for (int i = 2; i <= k; i++) for (int j = 1; j <= n; j++) for (int l = 1; j * l <= n; l++) f[i][j] = (f[i][j] + f[i - 1][j * l]) % mod;
	for (int i = 1; i <= n; i++) ans = (ans + f[k][i]) % M;
	printf("%lld\n", ans);
	return 0;
}