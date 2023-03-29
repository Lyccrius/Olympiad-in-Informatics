#include <iostream>

const int maxN = 1e5;
const int maxM = 1e5;

int T;
int n, m;
int a, b;
int x, k;

namespace graph {
	struct Vertex {
		int head;
	} vertex[maxN + 10];

	struct Edge {
		int head;
		int next;
	} edge[maxN * 2 + 10];

	int ecnt;

	void addEdge(int tail, int head) {
		ecnt++;
		edge[ecnt].head = head;
		edge[ecnt].next = vertex[tail].head;
		vertex[tail].head = ecnt;
		return;
	}

	int DFS(int u, int from, int k) {
		if (k == 0) return 1;
		int ret = 0;
		for (int e = vertex[u].head; e; e = edge[e].next) {
			int v = edge[e].head;
			if (v == from) continue;
			ret += DFS(v, u, k - 1);
		}
		return ret;
	}

	void clear() {
		for (int i = 1; i <= n; i++) vertex[i].head = 0;
		ecnt = 0;
		return;
	}
}

void mian() {
	std::cin >> n >> m;
	graph::clear();
	for (int i = 1; i < n; i++) {
		std::cin >> a >> b;
		graph::addEdge(a, b);
		graph::addEdge(b, a);
	}
	for (int i = 1; i <= m; i++) {
		std::cin >> x >> k;
		std::cout << graph::DFS(x, 0, k) << '\n';
	}
	return;
}

int main() {
	std::cin >> T;
	while (T--) mian();
	return 0;
}