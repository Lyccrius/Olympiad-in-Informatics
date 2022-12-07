#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxT = 50 + 10;
const int maxN = 50 + 10;
const int maxM = 2e5 + 10;

int T, N, M;
int P[maxT][maxN];
int F[maxM * maxN];

int main() {
	scanf("%d%d%d", &N, &T, &M);
	for (int i = 1; i <= N; i++) for (int j = 1; j <= T; j++) scanf("%d", &P[j][i]);
	for (int k = 1; k < T; k++) {
		std::memset(F, 0, sizeof(F));
		for (int i = 1; i <= N; i++) for (int j = P[k][i]; j <= M; j++) F[j] = std::max(F[j], F[j - P[k][i]] + P[k + 1][i] - P[k][i]);
		int m = 0;
		for (int i = 1; i <= M; i++) m = std::max(m, F[i]);
		M += m;
	}
	printf("%d\n", M);
	return 0;
}