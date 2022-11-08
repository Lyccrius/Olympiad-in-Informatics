#include <cstdio>
#include <algorithm>

const int maxn = 1e3 + 10;

int N, M, C;

long long val[maxn][maxn];
long long pre[maxn][maxn];

int main() {
	scanf("%d%d%d", &N, &M, &C);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			scanf("%lld", &val[i][j]);
			pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + val[i][j];
		}
	}
	long long ans = 0;
	int X, Y;
	for (int i = 1; i + C - 1<= N; i++) {
		for (int j = 1; j + C - 1<= M; j++) {
			long long S = pre[i + C - 1][j + C - 1] - pre[i - 1][j + C - 1] - pre[i + C - 1][j - 1] + pre[i - 1][j - 1];
			if (ans < S) {
				ans = S;
				X = i;
				Y = j;
			}
		}
	}
	printf("%d %d\n", X, Y);
	return 0;
}