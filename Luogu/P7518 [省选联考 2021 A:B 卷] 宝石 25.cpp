#include <iostream>
#include <set>

typedef std::set<int> sit;

const int maxN = 2e5;
const int maxQ = 2e5;
const int maxM = 5e4;
const int maxC = 5e4;

int n, m, c;
int P[maxC + 10];
int w[maxN + 10];
int u, v;
int q;
int s, t;

namespace graph {
	struct Vertex {
		int head;
	} vertex[maxN + 10];

	struct Edge {
		int head;
		int next;
	} edge[2 * maxN + 10];

	int ecnt;

	void addEdge(int tail, int head) {
		ecnt++;
		edge[ecnt].head = head;
		edge[ecnt].next = vertex[tail].head;
		vertex[tail].head = ecnt;
		return;
	}

	void DFS(int u, int t, int from, int cur) {
		if (w[u] == P[cur + 1]) cur++;
		if (u == t) {
			std::cout << cur << '\n';
			return;
		}
		for (int e = vertex[u].head; e; e = edge[e].next) {
			int v = edge[e].head;
			if (v == from) continue;
			DFS(v, t, u, cur);
		}
		return;
	}
}

int main() {
	std::cin >> n >> m >> c;
	for (int i = 1; i <= c; i++) std::cin >> P[i];
	for (int i = 1; i <= n; i++) std::cin >> w[i];
	for (int i = 1; i < n; i++) {
		std::cin >> u >> v;
		graph::addEdge(u, v);
		graph::addEdge(v, u);
	}
	std::cin >> q;
	for (int i = 1; i <= q; i++) {
		std::cin >> s >> t;
		graph::DFS(s, t, 0, 0);
	}
	return 0;
}