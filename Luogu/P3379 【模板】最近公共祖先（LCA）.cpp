#include <cstdio>
#include <algorithm>

const int maxN = 5e5 + 10;
const int maxM = 5e5 + 10;

int log[maxN];

int N, M, S;
int x, y;
int a, b;

namespace Graph {
	struct Vertex {
		int head;
		int depth;
		int fa[20];
	} vertex[maxN];
	struct Edge {
		int head;
		int next;
	} edge [maxN << 1];
	int ecnt;

	void AddEdge(int tail, int head) {
		ecnt++;
		edge[ecnt].head = head;
		edge[ecnt].next = vertex[tail].head;
		vertex[tail].head = ecnt;
		return;
	}

	void DFS(int u, int from) {
		vertex[u].fa[0] = from;
		vertex[u].depth = vertex[from].depth + 1;
		for (int i = 1; i <= log[vertex[u].depth]; i++) vertex[u].fa[i] = vertex[vertex[u].fa[i - 1]].fa[i - 1];
		for (int e = vertex[u].head; e; e = edge[e].next) {
			int v = edge[e].head;
			if (v != from) DFS(v, u);
		}
		return;
	}

	int LCA(int x, int y) {
		if (vertex[x].depth < vertex[y].depth) std::swap(x, y);
		while (vertex[x].depth > vertex[y].depth) x = vertex[x].fa[log[vertex[x].depth - vertex[y].depth] - 1];
		if (x == y) return x;
		for (int i = log[vertex[x].depth] - 1; i >= 0; i--) {
			if (vertex[x].fa[i] != vertex[y].fa[i]) {
				x = vertex[x].fa[i];
				y = vertex[y].fa[i];
			}
		}
		return vertex[x].fa[0];
	}
}

int main() {
	scanf("%d%d%d", &N, &M, &S);
	for (int i = 1; i < N; i++) scanf("%d%d", &x, &y), Graph::AddEdge(x, y), Graph::AddEdge(y, x);
	for (int i = 1; i <= N; i++) log[i] = log[i >> 1] + 1;
	Graph::DFS(S, 0);
	for (int i = 1; i <= M; i++) scanf("%d%d", &a, &b), printf("%d\n", Graph::LCA(a, b));
	return 0;
}