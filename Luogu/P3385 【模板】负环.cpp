#include <cstdio>
#include <queue>

const int maxN = 2e3 + 10;
const int maxM = 3e3 + 10;
const int inf = 1e9 + 10;

int T;
int n, m;
int u, v, w;

namespace Graph {
	struct Vertex {
		int dis;
		int head;
		int vis;
		int cnt;
	} vertex[maxN];
	struct Edge {
		int head;
		int next;
		int weight;
	} edge[maxM << 1];
	int ecnt;

	void Init() {
		ecnt = 0;
		for (int i = 1; i <= n; i++) vertex[i].cnt = 0;
		for (int i = 1; i <= n; i++) vertex[i].dis = inf;
		for (int i = 1; i <= n; i++) vertex[i].head = 0;
		for (int i = 1; i <= n; i++) vertex[i].vis = false;
		return;
	}

	void AddEdge(int tail, int head, int weight) {
		ecnt++;
		edge[ecnt].head = head;
		edge[ecnt].next = vertex[tail].head;
		edge[ecnt].weight = weight;
		vertex[tail].head = ecnt;
		return;
	}

	bool SPFA(int s) {
		vertex[s].dis = 0;
		std::queue<int> waiting;
		waiting.push(s);
		vertex[s].vis = true;
		while (!waiting.empty()) {
			int u = waiting.front();
			waiting.pop();
			vertex[u].vis = false;
			for (int e = vertex[u].head; e; e = edge[e].next) {
				int v = edge[e].head;
				int w = edge[e].weight;
				if (vertex[v].dis > vertex[u].dis + w) {
					vertex[v].dis = vertex[u].dis + w;
					vertex[v].cnt = vertex[u].cnt + 1;
					if (vertex[v].cnt >= n) return true;
					if (!vertex[v].vis) {
						vertex[v].vis = true;
						waiting.push(v);
					}
				}
			}
		}
		return false;
	}
}

void mian() {
	scanf("%d%d", &n, &m);
	Graph::Init();
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &u, &v, &w);
		if (w >= 0) {
			Graph::AddEdge(u, v, w);
			Graph::AddEdge(v, u, w);
		} else {
			Graph::AddEdge(u, v, w);
		}
	}
	if (Graph::SPFA(1)) printf("YES\n");
	else printf("NO\n");
	return;
}

int main() {
	scanf("%d", &T);
	while (T--) mian();
	return 0;
}