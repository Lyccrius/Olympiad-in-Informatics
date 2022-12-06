#include <cstdio>
#include <algorithm>

const int maxN = 10000 + 10;

int V, N, C;
int v[maxN], w[maxN];
int f[maxN];

int main() {
	scanf("%d%d%d", &V, &N, &C);
	for (int i = 1; i <= N; i++) scanf("%d%d", &v[i], &w[i]);
	for (int i = 1; i <= N; i++) {
		for (int j = C; j >= w[i]; j--) {
			f[j] = std::max(f[j], f[j - w[i]] + v[i]);
		}
	}
	if (f[C] < V) {
		printf("Impossible\n");
		return 0;
	}
	for (int i = 0; i <= V; i++) if (f[i] >= V) {
		printf("%d\n", C - i);
		break;
	}
	return 0;
}