#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn = 15 + 10;

int N;
int A[maxn];
int x[maxn][maxn];
int y[maxn][maxn];

bool check(long long S) {
	int state[maxn];
    std::memset(state, 0, sizeof(state));
	for (int i = 0; i < N; i++) if ((S >> i) & 1) state[i + 1] = 1;
	for (int i = 1; i <= N; i++) if (state[i]) {
		for (int j = 1; j <= A[i]; j++) {
			if (state[x[i][j]] != y[i][j]) return false;
		}
	}
	return true;
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &A[i]);
		for (int j = 1; j <= A[i]; j++) scanf("%d%d", &x[i][j], &y[i][j]);
	}
	int ans = 0;
	long long maxS = 1 << N;
	for (long long S = 1; S < maxS; S++) {
		if (check(S)) {
			int res = 0;
			for (int i = 0; i < 15; i++) if ((S >> i) & 1) res++;
			ans = std::max(ans, res);
		}
	}
	printf("%d\n", ans);
	return 0;
}