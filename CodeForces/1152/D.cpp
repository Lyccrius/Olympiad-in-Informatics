#include <cstdio>

const int maxn = 2000 + 5;
const int mod = 1e9 + 7;

int n;

int f[maxn][maxn];
int ans = 0;

int main() {
	scanf("%d", &n);

	f[1][1] = 1;
	for (int i = 2; i <= n + 1; i++) {
		for (int j = 1; j <= i; j++) {
			f[i][j] = (f[i - 1][j] + f[i][j - 1]) % mod;
			if ((i + j) & 1) {
				ans = (ans + f[i][j]) % mod;
			}
		}
	}

	printf("%d\n", ans);
	
	return 0;
}