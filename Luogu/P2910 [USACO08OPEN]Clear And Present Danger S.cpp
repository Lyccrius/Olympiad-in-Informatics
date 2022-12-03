#include <cstdio>
#include <algorithm>

const int maxN = 100 + 10;
const int maxM = 10000 + 10;

int N, M;
int A[maxM];
int D[maxN][maxN];
int ans;

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= M; i++) scanf("%d", &A[i]);
	for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) scanf("%d", &D[i][j]);
	for (int k = 1; k <= N; k++) for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) D[i][j] = std::min(D[i][j], D[i][k] + D[k][j]);
	for (int i = 1; i < M; i++) ans += D[A[i]][A[i + 1]];
	printf("%d\n", ans);
	return 0;
}