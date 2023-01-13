#include <cstdio>

const int maxN = 100 + 10;

int N, K;
int A[maxN];

int main() {
	scanf("%d%d", &N, &K);
	for (int i = 1; i <= N; i++) scanf("%d", &A[i]);
	for (int i = K + 1; i <= N; i++) printf("%d ", A[i]);
	for (int i = 1; i <= K && i <= N; i++) printf("0 ");
	return 0;
}