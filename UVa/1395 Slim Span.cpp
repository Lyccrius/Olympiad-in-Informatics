#include <iostream>
#include <algorithm>
#include <vector>

const int maxN = 100;
const int maxM = 5000;
const int inf = 1e9 + 10;

int n, m;
int u, v, w;
int ans;

namespace graph {
	struct Edge {
		int tail;
		int head;
		int weight;

		bool operator<(const Edge &other) const {
			return weight < other.weight;
		}
	};

	std::vector<Edge> edges;

	void addEdge(int tail, int head, int weight) {
		edges.push_back((Edge) {tail, head, weight});
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

	void Kruscal(int l) {
		int cnt = n;
		int res;
		DSU.Init();
        //printf("%d: w[%d] = %d\n", l, l, edges[l].weight);
		for (int r = l; r < edges.size(); r++) {
			int u = edges[r].tail;
			int v = edges[r].head;
			int w = edges[r].weight;
			int fu = DSU.Find(u);
			int fv = DSU.Find(v);
			if (fu == fv) continue;
			DSU.Union(u, v);
			cnt--;
			res = w - edges[l].weight;
            if (cnt == 1) break;
            //printf("%d: w[%d] = %d\n", l, r, edges[r].weight);
		}
		if (cnt == 1) ans = std::min(ans, res);
        //printf("res = %d\n", res);
		return;
	}

	void init() {
		edges.clear();
		ans = inf;
		return;
	}

	void mian() {
		std::sort(edges.begin(), edges.end());
		for (int l = 0; l < edges.size(); l++) Kruscal(l);
		if (ans >= inf) ans = - 1;
		std::cout << ans << '\n';
		return;
	}
}

void mian() {
	graph::init();
	for (int i = 1; i <= m; i++) {
		std::cin >> u >> v >> w;
		graph::addEdge(u, v, w);
	}
	graph::mian();
	return;
}

int main() {
	while (std::cin >> n >> m && n) mian();
	return 0;
}