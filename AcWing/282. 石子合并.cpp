#include <cstdio>
#include <algorithm>

const int inf = 1e9 + 10;
const int maxN = 300;

int N;
int w[maxN + 10];
int pre[maxN + 10];
int F[maxN + 10][maxN + 10];

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &w[i]);
		pre[i] = pre[i - 1] + w[i];
	}
	for (int len = 2; len <= N; len++) {
		for (int i = 1; i + len - 1 <= N; i++) {
			int j = i + len - 1;
			F[i][j] = inf;
			for (int k = i; k <= j; k++) {
				F[i][j] = std::min(F[i][j], F[i][k] + F[k + 1][j] + pre[j] - pre[i - 1]);
			}
		}
	}
	printf("%d\n", F[1][N]);
	return 0;
}