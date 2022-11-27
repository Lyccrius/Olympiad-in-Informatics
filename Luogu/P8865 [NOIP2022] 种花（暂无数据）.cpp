#include <cstdio>
#include <cstring>

const unsigned long long mod = 998244353;
const int maxN = 1e3 + 10;
const int maxM = 1e3 + 10;

int T, id;
int n, m, c, f;
int plant[maxN][maxM];
int right[maxN][maxM];
int lower[maxN][maxM];
int guaic[maxN][maxM];
int guaif[maxN][maxM];

int main() {
	scanf("%d%d", &T, &id);
	while (T--) {
		std::memset(plant, 1, sizeof(plant));
		std::memset(right, 0, sizeof(right));
		std::memset(lower, 0, sizeof(lower));
		std::memset(guaic, 0, sizeof(guaic));
		std::memset(guaif, 0, sizeof(guaif));
		scanf("%d%d%d%d", &n, &m, &c, &f);
		for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {char ch; scanf(" %c", &ch); plant[i][j] = ch - '0';}
		for (int i = n; i >= 1; i--) for (int j = m; j >= 1; j--) if (!plant[i][j]) {
			if (!plant[i][j + 1]) right[i][j] = right[i][j + 1] + 1;
			if (!plant[i + 1][j]) lower[i][j] = lower[i + 1][j] + 1;
            if (!plant[i + 1][j]) guaic[i][j] = guaic[i + 1][j] + right[i + 1][j];
            if (!plant[i][j]) guaif[i][j] = guaif[i + 1][j] + right[i + 1][j] * lower[i + 1][j];
		}
		unsigned long long Vc = 0;
		unsigned long long Vf = 0;
		for (int x1 = 1; x1 <= n; x1++) for (int y0 = 1; y0 <= m; y0++) if (!plant[x1][y0]) {
			Vc = (Vc + right[x1][y0] * guaic[x1 + 1][y0]) % mod;
            Vf = (Vf + right[x1][y0] * guaif[x1 + 1][y0]) % mod;
		}
		Vc = Vc * c % mod;
		Vf = Vf * f % mod;
		printf("%llu %llu\n", Vc, Vf);
	}
	return 0;
}