#include <cstdio>

const int maxN = 1000 + 10;
const int mod = 19650827;

int n;
int h[maxN];
long long f[maxN][maxN];

int main() {
	scanf("%d", &n);
  	for (int i = 1; i <= n; i++) scanf("%d", &h[i]);
	for (int i = 1; i <= n; i++) f[i][i] = 1;
  	for (int len = 2; len <= n; len++) {
  		for (int i = 1; i + len - 1 <= n; i++) {
  			int j = i + len - 1;
  			if (h[j - 1] < h[j]) f[i][j] += f[i][j - 1];
  			if (h[i] < h[i + 1]) f[j][i] += f[j][i + 1];
  			if (h[i] < h[j] && len != 2) f[i][j] += f[j - 1][i];
  			if (h[i] < h[j] && len != 2) f[j][i] += f[i + 1][j];
  			f[i][j] %=mod;
			f[j][i] %= mod;
  		}
  	}
  	printf("%lld\n", (f[1][n] + f[n][1]) % mod);
	return 0;
}