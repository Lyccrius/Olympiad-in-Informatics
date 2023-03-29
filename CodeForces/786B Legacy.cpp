#include <iostream>
#include <queue>

void promote() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	return;
}

typedef long long lxl;

const int maxN = 1e5;
const int maxQ = 1e5;
const int logN = 17;
const lxl inf = 1e18 + 10;

int n, q, s;
int opt;
int v, u;
int l, r;
int w;

namespace graph {
	struct Vertex {
		int vertex;
		int head;
		int vis;
		lxl dis;

		bool operator<(const Vertex &other) const {
			return dis > other.dis;
		}
	} vertex[2 * 4 * maxN + maxN + 10];

	struct Edge {
		int head;
		int next;
		int weight;
	} edge[maxQ + 2 * 2 * 4 * maxN + maxQ * logN + 10];

	int ecnt;

	void addEdge(int tail, int head, int weight) {
		ecnt++;
		edge[ecnt].head = head;
		edge[ecnt].next = vertex[tail].head;
		edge[ecnt].weight = weight;
		vertex[tail].head = ecnt;
		return;
	}

	void Dijkstra(int s) {
		for (int u = 1; u <= 2 * 4 * n + n; u++) vertex[u].vertex = u;
		for (int u = 1; u <= 2 * 4 * n + n; u++) vertex[u].dis = inf;
		vertex[s].dis = 0;
		std::priority_queue<Vertex> q;
		q.push(vertex[s]);
		while (!q.empty()) {
			int u = q.top().vertex;
			q.pop();
			if (vertex[u].vis) continue;
			vertex[u].vis = true;
			for (int e = vertex[u].head; e; e = edge[e].next) {
				int v = edge[e].head;
				int w = edge[e].weight;
				if (vertex[v].dis > vertex[u].dis + w) {
					vertex[v].dis = vertex[u].dis + w;
					q.push(vertex[v]);
				}
			}
		}
		return;
	}
}

struct SegmentTree {
	struct Node {
		int lson;
		int rson;
	} node[2 * 4 * maxN + 10];

	int ncnt;
	int rootI;
	int rootO;

	void BuildI(int &u, int l, int r) {
		if (!u) u = ++ncnt;
		if (l == r) {
			graph::addEdge(u, l, 0);
			return;
		}
		int mid = (l + r) / 2;
		BuildI(node[u].lson, l, mid); graph::addEdge(u, node[u].lson, 0);
		BuildI(node[u].rson, mid + 1, r); graph::addEdge(u, node[u].rson, 0);
		return;
	}

	void AddI(int u, int l, int r, int s, int t, int v, int w) {
		if (s <= l && r <= t) {
			graph::addEdge(v, u, w);
			return;
		}
		int mid = (l + r) / 2;
		if (s <= mid) AddI(node[u].lson, l, mid, s, t, v, w);
		if (t >= mid + 1) AddI(node[u].rson, mid + 1, r, s, t, v, w);
		return;
	}

	void BuildO(int &u, int l, int r) {
		if (!u) u = ++ncnt;
		if (l == r) {
			graph::addEdge(l, u, 0);
			return;
		}
		int mid = (l + r) / 2;
		BuildO(node[u].lson, l, mid); graph::addEdge(node[u].lson, u, 0);
		BuildO(node[u].rson, mid + 1, r); graph::addEdge(node[u].rson, u, 0);
		return;
	}

	void AddO(int u, int l, int r, int s, int t, int v, int w) {
		if (s <= l && r <= t) {
			graph::addEdge(u, v, w);
			return;
		}
		int mid = (l + r) / 2;
		if (s <= mid) AddO(node[u].lson, l, mid, s, t, v, w);
		if (t >= mid + 1) AddO(node[u].rson, mid + 1, r, s, t, v, w);
		return;
	}
} SGT;

int main() {
    promote();
	std::cin >> n >> q >> s;
	SGT.ncnt = n; 
	SGT.BuildI(SGT.rootI, 1, n);
	SGT.BuildO(SGT.rootO, 1, n);
	for (int i = 1; i <= q; i++) {
		std::cin >> opt;
		if (opt == 1) {
			std::cin >> v >> u >> w;
			graph::addEdge(v, u, w);
		} else if (opt == 2) {
			std::cin >> v >> l >> r >> w;
			SGT.AddI(SGT.rootI, 1, n, l, r, v, w);
		} else if (opt == 3) {
			std::cin >> v >> l >> r >> w;
			SGT.AddO(SGT.rootO, 1, n, l, r, v, w);
		}
	}
	graph::Dijkstra(s);
	for (int i = 1; i <= n; i++) {
		if (graph::vertex[i].dis >= inf) graph::vertex[i].dis = - 1;
		std::cout << graph::vertex[i].dis << ' ';
	}
	return 0;
}