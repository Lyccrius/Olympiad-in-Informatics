#include <cstdio>
#include <queue>

const int maxN = 5000 + 10;
const int maxM = 1e5 + 10;

int N, M;
int X, Y;

namespace Graph {
	struct Vertex {
		int head;
		int degree;
		int vis;
	} vertex[maxN];
	struct Edge {
		int head;
		int next;
	} edge[maxM];
	int ecnt;

	void AddEdge(int tail, int head) {
		ecnt++;
		edge[ecnt].head = head;
		edge[ecnt].next = vertex[tail].head;
		vertex[tail].head = ecnt;
		vertex[head].degree++;
		return;
	}

	int rank[maxN];
	int rcnt;

	bool TopoSort() {
		bool res = false;
		std::queue<int> waiting;
		int dcnt = 0;
		for (int i = 1; i <= N; i++) if (!vertex[i].degree) {
			waiting.push(i);
			dcnt++;
			if (dcnt > 1) res = true;
		}
		while (!waiting.empty()) {
			int u = waiting.front();
			waiting.pop();
			if (vertex[u].vis) continue;
			vertex[u].vis = true;
			rcnt++;
			rank[rcnt] = u;
			int cnt = 0;
			for (int e = vertex[u].head; e; e = edge[e].next) {
				int v = edge[e].head;
				vertex[v].degree--;
				if (!vertex[v].degree) {
					cnt++;
					waiting.push(v);
					if (cnt > 1) res = true;
				}
			}
		}
		return res;
	}
}

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= M; i++) scanf("%d%d", &X, &Y), Graph::AddEdge(X, Y);
	bool other = Graph::TopoSort();
	for (int i = 1; i <= N; i++) printf("%d\n", Graph::rank[i]);
	printf("%d\n", other);
	return 0;
}