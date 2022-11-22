#include <cstdio>
#include <algorithm>

const int maxN = 500;

int n;
int a[maxN];
int m;
int b[maxN];
int f[maxN][maxN];
int LCIS[maxN];

void Print(int x) {
	if (!x) return;
	Print(LCIS[x]);
	printf("%d ", b[x]);
	return;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) scanf("%d", &b[i]);
	for (int i = 1; i <= n; i++) {
		int t = 0;
		for (int j = 1; j <= m; j++) {
			if (a[i] == b[j]) {
				f[i][j] = f[i][t] + 1;
				LCIS[j] = t;
			}
			else f[i][j] = f[i - 1][j];
			if (b[j] < a[i]) if (f[i][t] < f[i][j]) t = j;
		}
	}
	int ans = 0;
	for (int i = 1; i <= m; i++) if (f[n][i] > f[n][ans]) ans = i;
	printf("%d\n", f[n][ans]);
	Print(ans);
	return 0;
}