#include <cstdio>

const int maxK = 100 + 10;
const int maxN = 1000 + 10;
const int maxM = 10000 + 10;

int K, N, M;
int graze[maxK];
int A, B;
int ans;

namespace Graph {
	struct Vertex {
		int head;
		int vis;
		int cnt;
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
		return;
	}

	void DFS(int u) {
		vertex[u].vis = true;
		vertex[u].cnt++;
		for (int e = vertex[u].head; e; e = edge[e].next) {
			int v = edge[e].head;
			if (vertex[v].vis == false) DFS(v);
		}
		return;
	}
}

int main() {
	scanf("%d%d%d", &K, &N, &M);
	for (int i = 1; i <= K; i++) scanf("%d", &graze[i]);
	for (int i = 1; i <= M; i++) scanf("%d%d", &A, &B), Graph::AddEdge(A, B);
	for (int i = 1; i <= K; i++) {
		for (int j = 1; j <= N; j++) Graph::vertex[j].vis = false;
		Graph::DFS(graze[i]);
	}
	for (int i = 1; i <= N; i++) if (Graph::vertex[i].cnt == K) ans++;
	printf("%d\n", ans);
	return 0;
}