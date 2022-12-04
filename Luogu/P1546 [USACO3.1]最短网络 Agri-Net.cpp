#include <cstdio>
#include <algorithm>

const int maxN = 100 + 10;

int N;

namespace Net {
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
	} edge[maxN * maxN];
	int ecnt;

	int adjacency[maxN][maxN];

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

	int Kruscal() {
		int res = 0;
		std::sort(edge + 1, edge + ecnt + 1);
		for (int i = 1; i <= ecnt; i++) {
			int u = edge[i].tail;
			int v = edge[i].head;
			int fu = Find(u);
			int fv = Find(v);
			if (fu == fv) continue;
			res += edge[i].weight;
			Union(u, v);
		}
		return res;
	}
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) {
		scanf("%d", &Net::adjacency[i][j]);
		if (Net::adjacency[i][j]) Net::AddEdge(i, j, Net::adjacency[i][j]);
	}
	Net::Init();
	int ans = Net::Kruscal();
	printf("%d\n", ans);
	return 0;
}