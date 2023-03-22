#include <iostream>
#include <algorithm>
#include <cstring>

const int maxN = 80;
const int maxK = 80;
const int maxM = 2000;

const int inf = 1e9 + 10;

int n, k;
int m;
int u, v, c;
int a[maxN + 10][maxN + 10];
int f[maxK + 10][maxN + 10][maxN + 10][2];
int maxC;
int ans = inf;

namespace graph {
	struct Vertex {
		int head;
		int vis;
	} vertex[maxN + 10];

	struct Edge {
		int head;
		int next;
		int weight;
	} edge[maxM + 10];

	int ecnt;

	void addEdge(int tail, int head, int weight) {
		ecnt++;
		edge[ecnt].head = head;
		edge[ecnt].next = vertex[tail].head;
		edge[ecnt].weight = weight;
		vertex[tail].head = ecnt;
		a[tail][head] = std::min(a[tail][head], weight);
		return;
	}
	
	void DP() {
		//std::memset(f, 0x3f, sizeof(f));
		std::memset(f[0], 1, sizeof(f[0]));
		for (int i = 1; i <= n; i++) {
			f[0][0][i][1] = 0;
			f[0][i][n + 1][0] = 0;
		}
		for (int t = 1; t < k; t++) {
			std::memset(f[t], 1, sizeof(f[t]));
			for (int i = 0; i <= n - 1; i++) {
				for (int j = i + 2; j <= n + 1; j++) {
					for (int l = i + 1; l <= j - 1; l++) {
						f[t][i][l][1] = std::min(f[t][i][l][1], f[t - 1][i][j][1] + a[j][l]);
						f[t][i][l][1] = std::min(f[t][i][l][1], f[t - 1][i][j][0] + a[i][l]);
						f[t][l][j][0] = std::min(f[t][l][j][0], f[t - 1][i][j][0] + a[i][l]);
						f[t][l][j][0] = std::min(f[t][l][j][0], f[t - 1][i][j][1] + a[j][l]);
					}
				}
			}
		}
		for (int i = 0; i <= n + 1; i++) {
			for (int j = 0; j <= n + 1; j++) {
				ans = std::min(ans, f[k - 1][i][j][0]);
				ans = std::min(ans, f[k - 1][i][j][1]);
			}
		}
		return;
	}
}

int main() {
	std::cin >> n >> k;
	std::cin >> m;
	std::memset(a, 1, sizeof(a));
	for (int i = 1; i <= m; i++) {
		std::cin >> u >> v >> c;
		//graph::addEdge(u, v, c);
		a[u][v] = std::min(a[u][v], c);
		maxC = std::max(maxC, c);
	}
	graph::DP();
	if (ans > m * maxC) ans = - 1;
	std::cout << ans << '\n';
	return 0;
}