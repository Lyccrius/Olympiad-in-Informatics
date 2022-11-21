#include <cstdio>
#include <algorithm>
#include <queue>

const int inf = 1e9 + 10;
const int maxN = 2000 + 10;

int N;
int r[maxN];
int p, m, f, n, s;
int S, T;

namespace Restaurant {
	struct Vertex {
		int head;
		int dis;
		int vis;
		int cur;
	};

	struct Edge {
		int head;
		int next;
		int c;
		int w;
	};

	Vertex vertex[maxN << 1];
	Edge edge[maxN * maxN << 1];
	int ecnt = 1;

	long long cost;

	void AddEdge(int tail, int head, int c, int w) {
		ecnt++;
		edge[ecnt].head = head;
		edge[ecnt].next = vertex[tail].head;
		vertex[tail].head = ecnt;
		edge[ecnt].c = c;
		edge[ecnt].w = w;
		ecnt++;
		edge[ecnt].head = tail;
		edge[ecnt].next = vertex[head].head;
		vertex[head].head = ecnt;
		edge[ecnt].c = 0;
		edge[ecnt].w = -w;
		return;
	}

	bool BFS() {
		for (int i = 0; i <= T; i++) {
			vertex[i].dis = inf;
			vertex[i].vis = false;
			vertex[i].cur = vertex[i].head;
		}
		std::queue<int> waiting;
		waiting.push(S);
		vertex[S].dis = 0;
		vertex[S].vis = true;
		while (!waiting.empty()) {
			int u = waiting.front();
			waiting.pop();
			vertex[u].vis = false;
			for (int i = vertex[u].head; i; i = edge[i].next) {
				int v = edge[i].head;
				int w = edge[i].w;
				if (vertex[v].dis > vertex[u].dis + w && edge[i].c) {
					vertex[v].dis = vertex[u].dis + w;
					if (!vertex[v].vis) {
						vertex[v].vis = true;
						waiting.push(v);
					}
				}
			}
		}
		return (vertex[T].dis != inf);
	}

	long long DFS(int u, int maxFlow) {
		if (u == T) return maxFlow;
		vertex[u].vis = true;
		int flow = 0;
		for (int &i = vertex[u].cur; i && flow < maxFlow; i = edge[i].next) {
			int v = edge[i].head;
			int w = edge[i].w;
			if (!vertex[v].vis && edge[i].c && vertex[v].dis == vertex[u].dis + w) {
				long long x = DFS(v, std::min(edge[i].c, maxFlow - flow));
				if (x) {
					cost += x * w;
					edge[i].c -= x;
					edge[i ^ 1].c += x;
					flow += x;
					if (flow == maxFlow) break;
				}
			}
		}
		return flow;
	}

	long long Dinic() {
		long long flow = 0;
		while (BFS()) {
			long long x;
			while ((x = DFS(S, inf))) {
				for (int i = S; i <= T; i++) vertex[i].vis = false;
				flow += x;
			}
		}
		return cost;
	}
}

int main() {
	scanf("%d", &N);
	S = 0;
	T = 2 * N + 1;
	for (int i = 1; i <= N; i++) scanf("%d", &r[i]);
	scanf("%d%d%d%d%d", &p, &m, &f, &n, &s);
	for (int i = 1; i <= N; i++) {
		Restaurant::AddEdge(S, i, r[i], 0);
		Restaurant::AddEdge(i + N, T, r[i], 0);
		Restaurant::AddEdge(S, i + N, inf, p);
		if (i + 1 <= N) Restaurant::AddEdge(i, i + 1, inf, 0);
		if (i + m <= N) Restaurant::AddEdge(i, i + N + m, inf, f);
		if (i + n <= N) Restaurant::AddEdge(i, i + N + n, inf, s);
	}
	long long cost = Restaurant::Dinic();
	printf("%lld\n", cost);
	return 0;
}