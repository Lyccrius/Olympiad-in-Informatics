#include <cstdio>
#include <algorithm>

const int maxN = 2e5 + 10;

int T;
int n;
int x, y;

namespace Rabbit {
	struct Node {
		int fa;
		int size;
		int head;
	};

	struct Edge {
		int head;
		int next;
	};

	Node node[maxN];
	Edge edge[maxN];
	int ecnt;

	void Init() {
		for (int i = 1; i <= n; i++) {
			node[i].fa = i;
			node[i].head = 0;
			node[i].size = 1;
		}
		ecnt = 0;
		return;
	}

	void AddEdge(int tail, int head) {
		ecnt++;
		edge[ecnt].head = head;
		edge[ecnt].next = node[tail].head;
		node[tail].head = ecnt;
		return;
	}

	int Find(int x) {
		if (node[x].fa == x) return x;
		return node[x].fa = Find(node[x].fa);
	}
}

void mian() {
	scanf("%d", &n);
	int res = 0;
	Rabbit::Init();
	for (int i = 1; i < n; i++) scanf("%d%d", &x, &y), Rabbit::AddEdge(std::max(x, y), std::min(x, y));
	for (int u = 1; u <= n; u++) {
		int cnt = 0;
		for (int e = Rabbit::node[u].head; e; e = Rabbit::edge[e].next) {
			int v = Rabbit::edge[e].head;
			v = Rabbit::Find(v);
			if (Rabbit::node[v].size) cnt++;
			Rabbit::node[u].size += Rabbit::node[v].size;
			Rabbit::node[v].fa = u;
		}
		if (cnt >= 2) {
			Rabbit::node[u].size -= 3;
			res++;
		}
	}
	printf("%d\n", res);
	return;
}

int main() {
	scanf("%d", &T);
	while (T--) mian();
	return 0;
}