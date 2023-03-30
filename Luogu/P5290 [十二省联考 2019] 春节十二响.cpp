#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

typedef long long lxl;
typedef std::vector<int> vic;
typedef std::priority_queue<int> pri;

const int maxN = 2e5;

int n;
int M[maxN + 10];
int f[maxN + 10];

namespace graph {
	struct Vertex {
		int head;
		pri heap;
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

	void Merge(int u, int v) {
		//printf("Merge %d, %d\n", u, v);
		if (vertex[u].heap.size() < vertex[v].heap.size()) std::swap(vertex[u].heap, vertex[v].heap);
		vic t;
		while (!vertex[v].heap.empty()) {
			t.push_back(std::max(vertex[u].heap.top(), vertex[v].heap.top()));
			vertex[u].heap.pop();
			vertex[v].heap.pop();
		}
		while (!t.empty()) {
			//printf("%d: %d\n", u, t.back());
			vertex[u].heap.push(t.back());
			t.pop_back();
		}
		return;
	}

	void DFS(int u, int from) {
		//printf("DFS %d from %d\n", u, from);
		for (int e = vertex[u].head; e; e = edge[e].next) {
			int v = edge[e].head;
			if (v == from) continue;
			DFS(v, u);
			Merge(u, v);
		}
		vertex[u].heap.push(M[u]);
		return;
	}

	void mian() {
		lxl ans = 0;
		while (!vertex[1].heap.empty()) {
			ans += vertex[1].heap.top();
			vertex[1].heap.pop();
		}
		std::cout << ans << '\n';
		return;
	}
}

int main() {
	std::cin >> n;
	for (int i = 1; i <= n; i++) std::cin >> M[i];
	for (int i = 2; i <= n; i++) std::cin >> f[i], graph::addEdge(f[i], i), graph::addEdge(i, f[i]);
	graph::DFS(1, 0);
	graph::mian();
	return 0;
}