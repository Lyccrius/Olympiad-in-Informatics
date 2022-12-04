#include <cstdio>
#include <algorithm>

const int maxN = 1e3 + 10;
const int maxM = 1e4 + 10;

int N, M, K;
int X, Y, L;

namespace Sky {
	struct Vertex {
		int fa;
	} vertex[maxN];

	struct Edge {
		int tail;
		int head;
		int weight;

		bool operator<(Edge other) const {
			return weight < other.weight;
		}
	} edge[maxM * 2];
	int ecnt;

	void AddEdge(int tail, int head, int weight) {
		ecnt++;
		edge[ecnt].tail = tail;
		edge[ecnt].head = head;
		edge[ecnt].weight = weight;
		return;
	}

	int Find(int x) {
		if (x == vertex[x].fa) return x;
		return vertex[x].fa = Find(vertex[x].fa);
	}

	void Union(int x, int y) {
		x = Find(x);
		y = Find(y);
		if (x == y) return;
		vertex[x].fa = y;
		return;
	}

	void Init() {
		for (int i = 1; i <= N; i++) vertex[i].fa = i;
		return;
	}

	int connected;

	int Kruscal() {
		int res = 0;
		std::sort(edge + 1, edge + ecnt + 1);
		for (int i = 1; i <= ecnt; i++) {
			int u = edge[i].tail;
			int v = edge[i].head;
			int fu = Find(u);
			int fv = Find(v);
			if (fu == fv) continue;
			Union(u, v);
			res += edge[i].weight;
			connected++;
			if (connected == N - K) return res;
		}
		return res;
	}
}

int main() {
	scanf("%d%d%d", &N, &M, &K);
	for (int i = 1; i <= M; i++) {
		scanf("%d%d%d", &X, &Y, &L);
		Sky::AddEdge(X, Y, L);
		Sky::AddEdge(Y, X, L);
	}
	Sky::Init();
	int ans = Sky::Kruscal();
	if (Sky::connected >= N - K) printf("%d\n", ans);
	else printf("No Answer\n");
	return 0;
}