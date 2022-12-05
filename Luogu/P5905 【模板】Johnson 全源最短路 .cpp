#include <cstdio>
#include <queue>

const int maxN = 3e3 + 10;
const int maxM = 6e3 + 10;
const int inf = 1e9;

int n, m;
int u, v, w;

namespace Graph {
	struct Vertex {
		int head;
		int ver;
		int vis;
		int his;
		int dis;
		int cnt;
		bool operator<(Vertex other) const {
			return dis > other.dis;
		}
	} vertex[maxN];
	struct Edge {
		int head;
		int next;
		int weight;
	} edge[maxN + maxM];
	int ecnt;

	void AddEdge(int tail, int head, int weight) {
		ecnt++;
		edge[ecnt].head = head;
		edge[ecnt].next = vertex[tail].head;
		edge[ecnt].weight = weight;
		vertex[tail].head = ecnt;
		return;
	}

	bool SPFA(int s) {
		std::queue<int> waiting;
		for (int u = 1; u <= n; u++) vertex[u].his = inf;
		for (int u = 1; u <= n; u++) vertex[u].vis = false;
		vertex[s].his = 0;
		waiting.push(s);
		while (!waiting.empty()) {
			int u = waiting.front();
			waiting.pop();
			vertex[u].vis = false;
			for (int e = vertex[u].head; e; e = edge[e].next) {
				int v = edge[e].head;
				int w = edge[e].weight;
				if (vertex[v].his > vertex[u].his + w) {
					vertex[v].his = vertex[u].his + w;
					vertex[v].cnt = vertex[u].cnt + 1;
					if (vertex[v].cnt > n) return true;
					if (vertex[v].vis == false) {
						vertex[v].vis = true;
						waiting.push(v);
					}
				}
			}
		}
		return false;
	}

	void Dijkstra(int s) {
		std::priority_queue<Vertex> waiting;
		for (int u = 1; u <= n; u++) vertex[u].ver = u;
		for (int u = 1; u <= n; u++) vertex[u].dis = inf;
		for (int u = 1; u <= n; u++) vertex[u].vis = false;
		vertex[s].dis = 0;
		waiting.push(vertex[s]);
		while (!waiting.empty()) {
			int u = waiting.top().ver;
			waiting.pop();
			if (vertex[u].vis) continue;
			vertex[u].vis = true;
			for (int e = vertex[u].head; e; e = edge[e].next) {
				int v = edge[e].head;
				int w = edge[e].weight;
				if (vertex[v].dis > vertex[u].dis + w) {
					vertex[v].dis = vertex[u].dis + w;
					if (vertex[v].vis == false) {
						waiting.push(vertex[v]);
					}
				}
			}
		}
		return;
	}

	void Johnson() {
		for (int u = 1; u <= n; u++) {
			for (int e = vertex[u].head; e; e = edge[e].next) {
				int v = edge[e].head;
				edge[e].weight += vertex[u].his - vertex[v].his;
			}
		}
		for (int s = 1; s <= n; s++) {
			Dijkstra(s);
			long long res = 0;
			for (int t = 1; t <= n; t++) {
				if (vertex[t].dis == inf) res += (long long)t * inf;
				else res += (long long)t * (vertex[t].dis + vertex[t].his - vertex[s].his);
			}
			printf("%lld\n", res);
		}
		return;
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) Graph::AddEdge(0, i, 0);
	for (int i = 1; i <= m; i++) scanf("%d%d%d", &u, &v, &w), Graph::AddEdge(u, v, w);
	if (Graph::SPFA(0)) {
		printf("-1\n");
		return 0;
	}
	Graph::Johnson();
	return 0;
}