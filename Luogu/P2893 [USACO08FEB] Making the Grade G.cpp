#include <cstdio>
#include <cmath>
#include <algorithm>

const int inf = 1e9 + 10;
const int maxN = 2000 + 10;

int N;
int A[maxN];
int B[maxN];
int F[maxN][maxN];

int Solve() {
	for (int i = 1; i <= N; i++) B[i] = A[i];
	std::sort(B + 1, B + N + 1);
	for (int i = 1; i <= N; i++) {
		int v = inf;
		for (int j = 1; j <= N; j++) {
			v = std::min(v, F[i - 1][j]);
			F[i][j] = v + std::abs(A[i] - B[j]);
		}
	}
	int res = inf;
	for (int i = 1; i <= N; i++) res = std::min(res, F[N][i]);
	return res;
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) scanf("%d", &A[i]);
	int res;
	res = Solve();
	std::reverse(A + 1, A + N + 1);
	res = std::min(res, Solve());
	printf("%d\n", res);
	return 0;
}