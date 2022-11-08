#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn = 300 + 10;
const int inf = 0x3f3f3f3f;

int N, M, K;
int A[maxn];
int B[maxn];

int sumA;
int sumB;
int F[maxn][maxn * maxn];

int main() {
	scanf("%d%d%d", &N, &M, &K);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &A[i]);
		sumA += A[i];
		if (A[i] < K) {
			printf("Impossible\n");
			return 0;
		}
	}
	for (int i = 1; i <= M; i++) scanf("%d", &B[i]);
	std::memset(F, -inf, sizeof(F));
	F[0][0] = 0;
	for (int i = 1; i <= M; i++) {
		for (int j = 0; j < B[i]; j++) F[i][j] = F[i - 1][j];
		sumB += B[i];
		for (int j = B[i]; j <= sumB; j++) F[i][j] = std::max(F[i - 1][j], F[i - 1][j - B[i]] + std::min(N, B[i]));
	}
	for (int j = sumA; j <= sumB; j++) if(F[M][j] >= N * K ) {
		printf("%d\n", j - sumA);
		return 0;
	}
	printf("Impossible\n");
	return 0;
}