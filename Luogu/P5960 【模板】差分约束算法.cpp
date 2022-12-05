#include <cstdio>
#include <queue>

const int maxN = 5e3 + 10;
const int maxM = 5e3 + 10;
const int inf = 1e9 + 10;

int n, m;
int c, c_, y;

namespace Graph {
	struct Vertex {
		int head;
		int vis;
		int dis;
		int cnt;
	} vertex[maxN];
	struct Edge {
		int head;
		int next;
		int weight;
	} edge [maxN + maxM];
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
		waiting.push(s);
		vertex[s].dis = 0;
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
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) Graph::vertex[i].dis = inf;
	for (int i = 1; i <= n; i++) Graph::AddEdge(0, i, 0);
	for (int i = 1; i <= m; i++) scanf("%d%d%d", &c, &c_, &y), Graph::AddEdge(c_, c, y);
	if (Graph::SPFA(0)) printf("NO\n");
	else for (int i = 1; i <= n; i++) printf("%d ", Graph::vertex[i].dis);
	return 0;
}