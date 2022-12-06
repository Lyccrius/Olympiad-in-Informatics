#include <cstdio>
#include <cmath>
#include <algorithm>

const int maxN = 1e3 + 10;

int n, k;
int x, y;

namespace Island {
	struct Vertex {
		int x, y;
		int head;
		int fa;
	} vertex[maxN];
	struct Edge {
		int tail;
		int head;
		int next;
		double weight;
		bool operator<(Edge other) const {
			return weight < other.weight;
		}
	} edge[maxN * maxN];
	int ecnt;

	double Dis(int u, int v) {
		double deltaX = vertex[u].x - vertex[v].x;
		double deltaY = vertex[u].y - vertex[v].y;
		double dis = std::sqrt(deltaX * deltaX + deltaY * deltaY);
		return dis;
	}

	void AddEdge(int tail, int head) {
		ecnt++;
		edge[ecnt].tail = tail;
		edge[ecnt].head = head;
		edge[ecnt].next = vertex[tail].head;
		edge[ecnt].weight = Dis(tail, head);
		vertex[tail].head = ecnt;
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

	double Kruscal() {
		std::sort(edge + 1, edge + ecnt + 1);
		for (int i = 1; i <= n; i++) vertex[i].fa = i;
		int cnt = 0;
		for (int e = 1; e <= ecnt; e++) {
			int tail = edge[e].tail;
			int head = edge[e].head;
			double weight = edge[e].weight;
			tail = Find(tail);
			head = Find(head);
			if (tail == head) continue;
			Union(tail, head);
			cnt++;
			if (cnt == n - k + 1) return weight;
		}
	}
}

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d%d", &Island::vertex[i].x, &Island::vertex[i].y);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) if (i != j) Island::AddEdge(i, j), Island::Dis(i, j);
	double ans = Island::Kruscal();
	printf("%.2lf\n", ans);
	return 0;
}