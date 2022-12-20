#include <cstdio>
#include <queue>

const int maxN = 1500 + 10;
const int maxM = 5e4 + 10;

int n, m;
int u, v, w;

namespace Graph {
	struct Vertex {
		int head;
		int vis;
		int dis;
	} vertex[maxN];

	struct Edge {
		int head;
		int next;
		int weight;
	} edge[maxM];

	int ecnt;

	void AddEdge(int tail, int head, int weight) {
		ecnt++;
		edge[ecnt].head = head;
		edge[ecnt].next = vertex[tail].head;
		edge[ecnt].weight = weight;
		vertex[tail].head = ecnt;
		return;
	}

	void SPFA(int s) {
		std::queue<int> waiting;
		waiting.push(s);
		while (!waiting.empty()) {
			int u = waiting.front();
			waiting.pop();
			vertex[u].vis = false;
			for (int e = vertex[u].head; e; e = edge[e].next) {
				int v = edge[e].head;
				int w = edge[e].weight;
				if (vertex[v].dis > vertex[u].dis + w) {
					vertex[v].dis = vertex[u].dis + w;
					if (vertex[v].vis == false) {
						vertex[v].vis = true;
						waiting.push(v);
					}
				}
			}
		}
		return;
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d%d%d", &u, &v, &w), Graph::AddEdge(u, v, -w);
	Graph::SPFA(1);
	if (Graph::vertex[n].dis) printf("%d\n", -Graph::vertex[n].dis);
	else printf("%d\n", -1);
	return 0;
}