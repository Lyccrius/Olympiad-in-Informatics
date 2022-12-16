#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxN = 50 + 10;
const int maxM = 10000 + 10;
const int inf = 1e9 + 10;

int n, m;
int u, v;

namespace Graph {
	int adj[maxN][maxN][64 + 10];
	int dis[maxN][maxN];

	void AddEdge(int tail, int head) {
		adj[tail][head][0] = true;
		dis[tail][head] = 1;
		return;
	}

	void Floyd() {
		for (int p = 1; p <= 64; p++) for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) if (adj[i][k][p - 1] && adj[k][j][p - 1]) adj[i][j][p] = true, dis[i][j] = 1;
		for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
		return;
	}

	void Init() {
		std::memset(dis, inf, sizeof(dis));
		return;
	}
}

int main() {
	Graph::Init();
	scanf("%d%d", &n, &m);
	while (m--) scanf("%d%d", &u, &v), Graph::AddEdge(u, v);
	Graph::Floyd();
	printf("%d\n", Graph::dis[1][n]);
	return 0;
}