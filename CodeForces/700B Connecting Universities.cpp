#include <iostream>

typedef long long lxl;

const int maxN = 2e5;
const int maxK = 1e5;

int n, k;
int u;
int x, y;
lxl ans;

namespace graph {
	struct Vertex {
		int head;
		int size;
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

	void DFS(int u, int from) {
		for (int e = vertex[u].head; e; e = edge[e].next) {
			int v = edge[e].head;
			if (v == from) continue;
			DFS(v, u);
			vertex[u].size += vertex[v].size;
		}
		ans += std::min(vertex[u].size, 2 * k - vertex[u].size);
		return;
	}
}

int main() {
	std::cin >> n >> k;
	for (int i = 1; i <= 2 * k; i++) {
		std::cin >> u;
		graph::vertex[u].size++;
	}
	for (int i = 1; i <= n - 1; i++) {
		std::cin >> x >> y;
		graph::addEdge(x, y);
		graph::addEdge(y, x);
	}
	graph::DFS(1, 0);
	std::cout << ans;
	return 0;
}