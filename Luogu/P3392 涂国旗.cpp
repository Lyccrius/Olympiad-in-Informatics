#include <cstdio>
#include <algorithm>

const int maxN = 50 + 10;
const int maxM = 50 + 10;
const int inf = 1e9 + 10;

int N, M;
char map[maxN][maxM];
int cnt[maxN][3];
int ans = inf;

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) {
		scanf(" %c", &map[i][j]);
		if (map[i][j] == 'W') cnt[i][0]++;
		if (map[i][j] == 'B') cnt[i][1]++;
		if (map[i][j] == 'R') cnt[i][2]++;
	}
	for (int i = 1; i < N; i++) for (int j = i + 1; j < N; j++) {
		int res = 0;
		for (int k = 1; k <= i; k++) res += M - cnt[k][0];
		for (int k = i + 1; k <= j; k++) res += M - cnt[k][1];
		for (int k = j + 1; k <= N; k++) res += M - cnt[k][2];
		ans = std::min(ans, res);
	}
	printf("%d\n", ans);
	return 0;
}