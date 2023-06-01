#include <iostream>

typedef long long lxl;

const int maxN = 1000;
const int mod = 998244353;

int n, a, b, c, d;
int C[maxN + 10][maxN + 10];
int P[maxN + 10][maxN + 10];

void init() {
	for (int i = 0; i <= maxN; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
		}
	}
	for (int i = 0; i <= maxN; i++) {
		P[i][0] = 1;
		for (int j = 1; j <= maxN; j++) {
			P[i][j] = (P[i][j - 1] + C[i][j]) % mod;
		}
	}
    return;
}

int calc(int x, int l, int r) {
	if (l > r) return 0;
	if (l <= 0) return P[x][r];
    return ((P[x][r] - P[x][l - 1]) % mod + mod) % mod;
}

lxl res;
lxl ans;

int main() {
    init();
    std::cin >> n >> a >> b >> c >> d;
	for (int i = 0; 4 * i <= n && i <= a && i <= b && i <= c && i <= d; i++) {
		res = 0;
		for (int j = 0; j <= n - 4 * i; j++) res = (res + 1ll * C[n - 4 * i][j] * calc(j, j - (b - i), a - i) % mod * calc(n - 4 * i - j, n - 4 * i - j - (c - i), d - i) % mod) % mod;
		res = res * C[n - 3 * i][i] % mod;
		if (i & 1) ans = (ans - res + mod) % mod;
		else ans = (ans + res) % mod;
	}
    std::cout << ans << '\n';
	return 0;
} 