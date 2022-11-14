#include <cstdio>
#include <vector>

const int maxn = 1000 + 10;

int T;
int n;
int s, k;

namespace Network {
	struct Vertex {
		bool covered;
        int ecnt;
		int from;
		int head;
	};
	
	struct Edge {
		int head;
		int next;
	};

	Vertex vertex[maxn];
	Edge edge[maxn * 2];
	int ecnt;
	std::vector<int> nodes[maxn];

	void AddEdge(int tail, int head) {
		ecnt++;
		edge[ecnt].head = head;
		edge[ecnt].next = vertex[tail].head;
		vertex[tail].head = ecnt;
        vertex[tail].ecnt++;
		return;
	}

	void SetRoot(int u, int from, int depth) {
		vertex[u].from = from;
		if (vertex[u].ecnt == 1 && depth > k) nodes[depth].push_back(u);
		for (int i = vertex[u].head; i; i = edge[i].next) {
			int v = edge[i].head;
			if (v != from) SetRoot(v, u, depth + 1);
		}
		return;
	}

	void DFS(int u, int from, int depth) {
		vertex[u].covered = true;
		for (int i = vertex[u].head; i; i = edge[i].next) {
			int v = edge[i].head;
			if (v != from && depth < k) DFS(v, u, depth + 1);
		}
		return;
	}

	int solve() {
		int ans = 0;
		for (int i = 1; i <= n; i++) vertex[i].covered = false;
		for (int depth = n - 1; depth > k; depth--) for (int i = 0; i < nodes[depth].size(); i++) {
			int u = nodes[depth][i];
			if (vertex[u].covered) continue;
			int v = u;
			for (int j = 1; j <= k; j++) v = vertex[v].from;
			DFS(v, 0, 0);
			ans++;
		}
		return ans;
	}
}

int main() {
	scanf("%d", &T);
	for (int kase = 1; kase <= T; kase++) {
		scanf("%d", &n);
		scanf("%d%d", &s, &k);
        for (int i = 1; i <= n; i++) {
            Network::vertex[i].ecnt = 0;
            Network::vertex[i].head = 0;
            Network::ecnt = 0;
            Network::nodes[i].clear();
        }
		for (int i = 1; i < n; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			Network::AddEdge(u, v);
			Network::AddEdge(v, u);
		}
		Network::SetRoot(s, 0, 0);
		printf("%d\n", Network::solve());
	}
	return 0;
}