#include <cstdio>
#include <algorithm>
#include <queue>

const int maxN = 2500 + 10;
const int maxM = 10000 + 10;
const int maxK = 100 + 10;

const int A = 1;

int n, m, k;
long long s[maxN];
int x, y;

namespace Holiday {
	struct Vertex {
		int dis;
		int head;
		long long s;
	};

	struct Edge {
		int head;
		int next;
	};

	Vertex vertex[maxN];
	Edge edge[maxM * 2];
	int ecnt;

	void AddEdge(int tail, int head) {
		ecnt++;
		edge[ecnt].head = head;
		edge[ecnt].next = vertex[tail].head;
		vertex[tail].head = ecnt;
	}

	int adjacency[maxN][maxN];
	int maxB[maxN][3];

	void PreWork() {
		for (int s = 1; s <= n; s++) {
			for (int u = 1; u <= n; u++) vertex[u].dis = 0;
			std::queue<int> waiting;
			waiting.push(s);
			while (!waiting.empty()) {
				int u = waiting.front();
				waiting.pop();
				for (int e = vertex[u].head; e; e = edge[e].next) {
					int v = edge[e].head;
					if (vertex[v].dis) continue;
					vertex[v].dis = vertex[u].dis + 1;
					waiting.push(v);
				}
			}
			for (int t = 1; t <= n; t++) if (vertex[t].dis && vertex[t].dis <= k + 1) adjacency[s][t] = true;
		}
		for (int C = 2; C <= n; C++) for (int B = 2; B <= n; B++) if (B != C && adjacency[A][B] && adjacency[B][C]) {
			int nowB = B;
			for (int i = 1; i <= 3; i++) if (vertex[maxB[C][i]].s < vertex[nowB].s) std::swap(maxB[C][i], nowB);
		}
		return;
	}

	void Solve() {
		long long ans = 0;
		for (int C = 2; C <= n; C++) for (int D = C + 1; D <= n; D++) if (adjacency[C][D]) {
			for (int i = 1; i <= 3; i++) for (int j = 1; j <= 3; j++) {
				int B = maxB[C][i];
				int E = maxB[D][j];
				if (B && E && B != D && B != E && C != E) ans = std::max(ans, vertex[B].s + vertex[C].s + vertex[D].s + vertex[E].s);
			}
		}
		printf("%lld\n", ans);
		return;
	}
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 2; i <= n; i++) scanf("%lld", &s[i]), Holiday::vertex[i].s = s[i];
	for (int i = 1; i <= m; i++) scanf("%d%d", &x, &y), Holiday::AddEdge(x, y), Holiday::AddEdge(y, x);
	Holiday::PreWork();
	Holiday::Solve();
	return 0;
}