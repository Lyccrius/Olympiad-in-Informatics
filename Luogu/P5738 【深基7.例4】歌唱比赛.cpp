#include <cstdio>
#include <algorithm>

const int maxN = 100 + 10;
const int maxM = 20 + 10;

int n, m;
int sco[maxN][maxM];
int tot[maxN];
double res[maxN];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf("%d", &sco[i][j]);
	for (int i = 1; i <= n; i++) std::sort(sco[i] + 1, sco[i] + m + 1);
	for (int i = 1; i <= n; i++) for (int j = 2; j < m; j++) tot[i] += sco[i][j];
	for (int i = 1; i <= n; i++) res[i] = (double)tot[i] / (m - 2);
	std::sort(res + 1, res + n + 1);
	printf("%.2lf", res[n]);
	return 0;
}