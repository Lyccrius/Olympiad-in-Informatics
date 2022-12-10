#include <cstdio>
#include <algorithm>

const int maxN = 1000 + 10;

int N, C;
long long W[maxN];
long long P[maxN];
long long ans = 0;

void DFS(int now, long long res) {
	if (P[now] + res <= ans) return;
	ans = std::max(res, ans);
	for (int i = now; i >= 1; i--) if (res + W[i] <= C) DFS(i - 1, res + W[i]);
	return;
}

int main() {
	scanf("%d%d", &N, &C);
	for (int i = 1; i <= N; i++) scanf("%lld", &W[i]), P[i] = P[i - 1] + W[i];
	DFS(N, 0);
	printf("%lld\n", ans);
	return 0;
}