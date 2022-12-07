#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxT = 100 + 10;
const int maxN = 100 + 10;
const int maxM = 1e3 + 10;

int T, N, M;
int P[maxT][maxN];
int F[maxM * maxN];

int main() {
	scanf("%d%d%d", &T, &N, &M);
	for (int i = 1; i <= T; i++) for (int j = 1; j <= N; j++) scanf("%d", &P[i][j]);
	for (int k = 1; k < T; k++) {
		std::memset(F, 0, sizeof(F));
		for (int i = 1; i <= N; i++) for (int j = P[k][i]; j <= M; j++) F[j] = std::max(F[j], F[j - P[k][i]] + P[k + 1][i] - P[k][i]);
		M += F[M];
	}
	printf("%d\n", M);
	return 0;
}