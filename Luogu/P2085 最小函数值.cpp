#include <cstdio>
#include <queue>

const int maxN = 10000 + 10;
const int maxM = 10000 + 10;
const int inf = 1e9 + 10;

int n, m;
int A[maxN], B[maxN], C[maxN];
int cur[maxN];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d%d%d", &A[i], &B[i], &C[i]), cur[i] = 1;
	for (int i = 1; i <= m; i++) {
		int ans = inf;
		int pos = 0;
		for (int j = 1; j <= n; j++) {
			int F = A[j] * cur[j] * cur[j] + B[j] * cur[j] + C[j];
			if (ans > F) {
				ans = F;
				pos = j;
			}
		}
		printf("%d ", ans);
		cur[pos]++;
	}
	printf("\n");
	return 0;
}