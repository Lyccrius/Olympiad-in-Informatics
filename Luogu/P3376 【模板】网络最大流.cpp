#include <iostream>
#include <vector>
#include <deque>

void promote() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	return;
}

typedef long long lxl;
typedef std::vector<int> vic;
typedef std::deque<int> dic;

const int maxN = 200;
const int maxM = 5000;
const lxl maxW = (1ll << 31) - 1;

int n, m, s, t;
int u, v, w;

namespace graph {
	struct Vertex {
		vic edge;
		int flow;
		int from;
	} vertex[maxN + 10];

	struct Edge {
		int tail;
		int head;
		int capacity;
		int flow;
	};

	std::vector<Edge> edges;

	void addEdge(int tail, int head, int weight) {
		edges.push_back((Edge) {tail, head, weight, 0});
		edges.push_back((Edge) {head, tail, 0, 0});
		vertex[tail].edge.push_back(edges.size() - 2);
		vertex[head].edge.push_back(edges.size() - 1);
		return;
	}

	bool BFS() {
		for (int u = 1; u <= n; u++) vertex[u].flow = 0;
		vertex[s].flow = maxW;
		dic q;
		q.push_back(s);
		while (!q.empty()) {
			int u = q.front();
			q.pop_front();
			for (auto e : vertex[u].edge) {
				int v = edges[e].head;
				int c = edges[e].capacity;
				int f = edges[e].flow;
				if (vertex[v].flow == 0 && c > f) {
					vertex[v].flow = std::min(vertex[u].flow, c - f);
					vertex[v].from = e;
					q.push_back(v);
				}
			}
			if (vertex[t].flow) break;
		}
		return vertex[t].flow;
	}

	lxl EdmondsKarp() {
		lxl flow = 0;
		while (BFS()) {
			for (int u = t; u != s; u = edges[vertex[u].from].tail) {
				edges[vertex[u].from].flow += vertex[t].flow;
				edges[vertex[u].from ^ 1].flow -= vertex[t].flow;
			}
			flow += vertex[t].flow;
		}
		return flow;
	}
}

int main() {
    promote();
	std::cin >> n >> m >> s >> t;
	for (int i = 1; i <= m; i++) {
		std::cin >> u >> v >> w;
		graph::addEdge(u, v, w);
	}
	std::cout << graph::EdmondsKarp();
	return 0;
}