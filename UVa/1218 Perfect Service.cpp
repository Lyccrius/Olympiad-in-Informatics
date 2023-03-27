#include <iostream>
#include <algorithm>

void promote() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	return;
}

const int maxN = 1e4;
const int inf = 1e4 + 10;

int N;
int a, b;

namespace graph {
	struct Vertex {
		int head;
		int f[4];
	} vertex[maxN + 10];

	struct Edge {
		int head;
		int next;
	} edge[2 * maxN + 10];

	int ecnt;

	void addEdge(int tail, int head) {
		//printf("AddEdge %d to %d\n", tail, head);
		ecnt++;
		edge[ecnt].head = head;
		edge[ecnt].next = vertex[tail].head;
		vertex[tail].head = ecnt;
		return;
	}

	void init() {
		for (int i = 1; i <= N; i++) vertex[i].head = 0;
		ecnt = 0;
		return;
	}

	void DFS(int u, int from) {
		//printf("DFS %d from %d\n", u, from);
		vertex[u].f[0] = 1;
		vertex[u].f[1] = 0;
		vertex[u].f[2] = inf;
		for (int e = vertex[u].head; e; e = edge[e].next) {
			int v = edge[e].head;
			if (v == from) continue;
			DFS(v, u);
		}
		for (int e = vertex[u].head; e; e = edge[e].next) {
			int v = edge[e].head;
			if (v == from) continue;
			vertex[u].f[0] += std::min(vertex[v].f[0], vertex[v].f[1]);
			vertex[u].f[1] += vertex[v].f[2];
		}
		for (int e = vertex[u].head; e; e = edge[e].next) {
			int v = edge[e].head;
			if (v == from) continue;
			vertex[u].f[2] = std::min(vertex[u].f[2], vertex[u].f[1] - vertex[v].f[2] + vertex[v].f[0]);
			//vertex[u].f[2] = std::min(vertex[u].f[2], vertex[v].f[0]);
		}
		return;
	}
}

void mian() {
	if (N == 0) return;
	graph::init();
	for (int i = 1; i < N; i++) {
		std::cin >> a >> b;
		graph::addEdge(a, b);
		graph::addEdge(b, a);
	}
	graph::DFS(1, 0);
	std::cout << std::min(graph::vertex[1].f[0], graph::vertex[1].f[2]) << '\n';
	return;
}

int main() {
	while (std::cin >> N && (~N)) mian();
	return 0;
}