#include <cstdio>
#include <algorithm>

const int maxN = 2e4 + 10;
const int inf = 1e9 + 10;

int N, M;
int minS[maxN];
int minV[maxN];
int ans = inf;

void DFS(int dep, int r, int h, int s, int v) {
	int maxH = h;
	if (dep == 0) {
		if(v == N) ans = std::min(ans, s);
		return;
	}
	if (s + minS[dep - 1] >= ans) return;
	if (v + minV[dep - 1] > N) return;
	if (2 * (N - v) / r + s >= ans) return;
	for (int i = r - 1; i >= dep; i--) {
		if (dep == M) s = i * i;
		maxH = std::min(h - 1, (N - minV[dep - 1] - v) / i / i);
		for (int j = maxH; j >= dep; j--) DFS(dep - 1, i, j, s + 2 * i * j, v + i * i * j);
	}
	return;
}

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= M; i++) {
		minS[i] = minS[i - 1] + 2 * i * i;
		minV[i] = minV[i] + i * i * i;
	}
	DFS(M, N, N, 0, 0);
	if (ans == inf) ans = 0;
	printf("%d\n", ans);
	return 0;
}