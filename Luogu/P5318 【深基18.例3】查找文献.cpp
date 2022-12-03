#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>

const int maxN = 1e5 + 10;
const int maxM = 1e6 + 10;

int n, m;
int X, Y;

namespace Literature {
	struct Vertex {
		bool vis;
	} vertex[maxN];
	std::vector<int> edge[maxN];

	void AddEdge(int tail, int head) {
		edge[tail].push_back(head);
		return;
	}

	void Init() {
		for (int i = 1; i <= n; i++) vertex[i].vis = false;
		for (int i = 1; i <= n; i++) std::sort(edge[i].begin(), edge[i].end());
		return;
	}

	void DFS(int u) {
		if (vertex[u].vis) return;
		printf("%d ", u);
		vertex[u].vis = true;
		for (auto v : edge[u]) DFS(v);
		return;
	}

	void BFS(int u) {
		std::queue<int> waiting;
		waiting.push(u);
		while (!waiting.empty()) {
			int u = waiting.front();
			waiting.pop();
			if (vertex[u].vis) continue;
			printf("%d ", u);
			vertex[u].vis = true;
			for (auto v : edge[u]) waiting.push(v);
		}
		return;
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d%d", &X, &Y), Literature::AddEdge(X, Y);
	Literature::Init();
	Literature::DFS(1);
	printf("\n");
	Literature::Init();
	Literature::BFS(1);
	return 0;
}