#include <iostream>
#include <algorithm>

const int maxN = 1e5;
const int maxM = 1e6;
const int maxE = 1e9;

int n, m;
int a, b, e;

namespace graph {
	struct Edge {
		int tail;
		int head;
		int weight;

		bool operator<(const Edge &other) const {
			return weight < other.weight;
		}
	} edge[maxM + 10];

	int ecnt;

	void addEdge(int tail, int head, int weight) {
		ecnt++;
		edge[ecnt].tail = tail;
		edge[ecnt].head = head;
		edge[ecnt].weight = weight;
		return;
	}

	struct DisjointSetUnion {
		struct Node {
			int fa;
		} node[maxN + 10];

		void Init() {
			for (int i = 1; i <= n; i++) {
				node[i].fa = i;
			}
			return;
		}

		int Find(int u) {
			if (node[u].fa == u) return u;
			return node[u].fa = Find(node[u].fa);
		}

		void Union(int u, int v) {
			int fu = Find(u);
			int fv = Find(v);
			if (fu == fv) return;
			node[fu].fa = fv;
			return;
		}
	} DSU;

	void Kruscal() {
		DSU.Init();
		std::sort(edge + 2, edge + m + 1);
		for (int e = 2; e <= m; e++) {
			int u = edge[e].tail;
			int v = edge[e].head;
			int w = edge[e].weight;
			int fu = DSU.Find(u);
			int fv = DSU.Find(v);
			if (fu == fv) continue;
			DSU.Union(u, v);
			u = edge[1].tail;
			v = edge[1].head;
			fu = DSU.Find(u);
			fv = DSU.Find(v);
			if (fu == fv) {
				std::cout << w;
				return;
			}
		}
		std::cout << maxE;
		return;
	}
}

int main() {
	std::cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		std::cin >> a >> b >> e;
		graph::addEdge(a, b, e);
	}
	graph::Kruscal();
	return 0;
}