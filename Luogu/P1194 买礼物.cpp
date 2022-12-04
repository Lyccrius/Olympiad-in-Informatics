#include <cstdio>
#include <algorithm>

const int maxB = 500 + 10;

int A, B;
int K[maxB][maxB];

namespace Market {
	struct Vertex {
		int fa;
	} vertex[maxB];

	struct Edge {
		int tail;
		int head;
		int weight;

		bool operator<(Edge other) const {
			return weight < other.weight;
		}
	} edge[maxB * maxB];
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
		for (int i = 1; i <= B; i++) Market::AddEdge(0, i, A);
		for (int i = 1; i <= B; i++) vertex[i].fa = i;
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
	scanf("%d%d", &A, &B);
	for (int i = 1; i <= B; i++) for (int j = 1; j <= B; j++) {
		scanf("%d", &K[i][j]);
		if (K[i][j]) Market::AddEdge(i, j, K[i][j]);
	}
	Market::Init();
	int ans = Market::Kruscal();
	printf("%d\n", ans);
	return 0;
}