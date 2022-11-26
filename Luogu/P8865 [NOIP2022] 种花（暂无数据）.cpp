#include <cstdio>
#include <cstring>

const int mod = 998244353;
const int maxN = 1e3 + 10;
const int maxM = 1e3 + 10;

int T, id;
int n, m, c, f;
int plant[maxN][maxM];
int right[maxN][maxM];
int lower[maxN][maxM];

int main() {
	scanf("%d%d", &T, &id);
	while (T--) {
		std::memset(right, 0, sizeof(right));
		std::memset(lower, 0, sizeof(lower));
		scanf("%d%d%d%d", &n, &m, &c, &f);
		for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {char ch; scanf(" %c", &ch); plant[i][j] = ch - '0';}
		for (int i = n; i >= 1; i--) for (int j = m; j >= 1; j--) if (!plant[i][j]) {
			right[i][j] = right[i][j + 1] + 1;
			lower[i][j] = lower[i + 1][j] + 1;
		}
		long long Vc = 0;
		long long Vf = 0;
		for (int x1 = 1; x1 <= n; x1++) for (int y0 = 1; y0 <= m; y0++) if (!plant[x1][y0]) {
			if (right[x1][y0] <= 1 || lower[x1][y0] <= 1) continue;
			for (int x2 = x1 + 2; x2 <= x1 + lower[x1][y0]; x2++) {
				if (right[x2][y0] > 1) Vc = (Vc + (right[x1][y0] - 1) * (right[x2][y0] - 1)) % mod;
				if (lower[x2][y0] > 1) Vf = (Vf + (right[x1][y0] - 1) * (right[x2][y0] - 1) * (lower[x2][y0] - 1)) % mod;
			}
		}
		Vc = Vc * c % mod;
		Vf = Vf * f % mod;
		printf("%lld %lld\n", Vc, Vf);
	}
	return 0;
}