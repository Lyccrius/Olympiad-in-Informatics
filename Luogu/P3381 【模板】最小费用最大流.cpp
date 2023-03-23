#include <iostream>
#include <vector>
#include <deque>

void promote() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	return;
}

typedef std::vector<int> vic;
typedef std::deque<int> dic;

const int maxN = 5e3;
const int maxM = 5e4;
const int maxW = 1e3;
const int maxC = 1e3;
const int inf = 1e9 + 10;

int n, m, s, t;
int u, v, w, c;

namespace graph {
	struct Vertex {
		vic edge;
		int flow;
		int cost;
		int from;
		int inq;
	} vertex[maxN + 10];

	struct Edge {
		int tail;
		int head;
		int capacity;
		int flow;
		int cost;
	};

	std::vector<Edge> edges;

	void addEdge(int tail, int head, int weight, int cost) {
		edges.push_back((Edge) {tail, head, weight, 0, cost});
		edges.push_back((Edge) {head, tail, 0, 0, - cost});
		vertex[tail].edge.push_back(edges.size() - 2);
		vertex[head].edge.push_back(edges.size() - 1);
		return;
	}

	bool SPFA() {
		for (int u = 1; u <= n; u++) vertex[u].cost = inf;
		for (int u = 1; u <= n; u++) vertex[u].inq = false;
		vertex[s].flow = inf;
		vertex[s].cost = 0;
		vertex[s].inq = true;
		dic q;
		q.push_back(s);
		while (!q.empty()) {
			int u = q.front();
			q.pop_front();
			vertex[u].inq = false;
			for (auto e : vertex[u].edge) {
				int v = edges[e].head;
				int capacity = edges[e].capacity;
				int flow = edges[e].flow;
				int cost = edges[e].cost;
				if (vertex[v].cost > vertex[u].cost + cost && capacity > flow) {
					vertex[v].cost = vertex[u].cost + cost;
					vertex[v].flow = std::min(vertex[u].flow, capacity - flow);
					vertex[v].from = e;
					if (vertex[v].inq == false) {
						vertex[v].inq = true;
						q.push_back(v);
					}
				}
			}
		}
		return vertex[t].cost < inf;
	}

	int flow;
	int cost;

	void MinCostMaxFlow() {
		while (SPFA()) {
			for (int u = t; u != s; u = edges[vertex[u].from].tail) {
				edges[vertex[u].from].flow += vertex[t].flow;
				edges[vertex[u].from ^ 1].flow -= vertex[t].flow;
			}
			flow += vertex[t].flow;
			cost += vertex[t].flow * vertex[t].cost;
		}
		return;
	}
}

int main() {
	promote();
	std::cin >> n >> m >> s >> t;
	for (int i = 1; i <= m; i++) {
		std::cin >> u >> v >> w >> c;
		graph::addEdge(u, v, w, c);
	}
	graph::MinCostMaxFlow();
	std::cout << graph::flow << ' ' << graph::cost;
	return 0;
}