#include <cstdio>
#include <queue>

const int maxN = 1e6 + 10;
const int maxM = 2e6 + 10;
const int mod = 100003;

int N, M;
int x, y;

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
	} edge[maxM << 1];
	int ecnt;
	
	void AddEdge(int tail, int head) {
		ecnt++;
		edge[ecnt].head = head;
		edge[ecnt].next = vertex[tail].head;
		vertex[tail].head = ecnt;
		return;
	}

	void BFS(int s) {
		std::queue<int> waiting;
		waiting.push(s);
		vertex[s].cnt = 1;
		vertex[s].vis = true;
		while (!waiting.empty()) {
			int u = waiting.front();
			waiting.pop();
			for (int e = vertex[u].head; e; e = edge[e].next) {
				int v = edge[e].head;
				if (!vertex[v].vis) {
					vertex[v].vis = true;
					vertex[v].dis = vertex[u].dis + 1;
					waiting.push(v);
				}
				if (vertex[v].dis == vertex[u].dis + 1) {
					vertex[v].cnt += vertex[u].cnt;
					vertex[v].cnt %= mod;
				}
			}
		}
		return;
	}
}

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= M; i++) scanf("%d%d", &x, &y), Graph::AddEdge(x, y), Graph::AddEdge(y, x);
	Graph::BFS(1);
	for (int i = 1; i <= N; i++) printf("%d\n", Graph::vertex[i].cnt);
	return 0;
}