#include <cstdio>

const int maxN = 30 + 10;

int n;
long long sco[maxN];
long long f[maxN][maxN];
long long root[maxN][maxN];

void print(int l, int r) {
	if (l > r)return;
	printf("%lld ", root[l][r]);
	print(l, root[l][r] - 1);
	print(root[l][r] + 1, r);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", &sco[i]);
	for (int i = 1; i <= n; i++) f[i][i] = sco[i];
	for (int i = 1; i <= n; i++) f[i][i - 1] = 1;
	for (int i = 1; i <= n; i++) root[i][i] = i;
	for (int len = 2; len <= n; len++) {
		for (int i = 1; i + len - 1 <= n; ++i) {
			int j = i + len - 1;
			f[i][j] = f[i + 1][j] + f[i][i];
			root[i][j] = i;
			for (int k = i + 1; k < j; k++) {
				if (f[i][j] < f[i][k - 1] * f[k + 1][j] + f[k][k]) {
					f[i][j] = f[i][k - 1] * f[k + 1][j] + f[k][k];
					root[i][j] = k;
				}
			}
		}
	}
	printf("%lld\n", f[1][n]);
	print(1, n);
	return 0;
}