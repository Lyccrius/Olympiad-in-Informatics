#include <iostream>

void promote() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	return;
}

const int maxN = 1e5;
const int maxM = 1e5;
const int maxR = 1e5;
const int maxP = (1ll << 31) - 1;

int n, m, r, p;
int o, x, y, z;
int a[maxN + 10];
int b[maxN + 10];

namespace graph {
	struct Vertex {
		int head;
		int dep;
		int fu;
		int size;
		int hson;
		int dfn;
		int top;
	} vertex[maxN + 10];

	struct Edge {
		int head;
		int next;
	} edge[maxM * 2 + 10];

	int ecnt;

	void addEdge(int tail, int head) {
		ecnt++;
		edge[ecnt].head = head;
		edge[ecnt].next = vertex[tail].head;
		vertex[tail].head = ecnt;
		//printf("addEdge %d to %d at %d\n", tail, head, ecnt);
		return;
	}

	void DFS1(int u, int fu) {
		vertex[u].dep = vertex[fu].dep + 1;
		vertex[u].fu = fu;
		vertex[u].size = 1;
		//printf("fa[%d] = %d\n", u, vertex[u].fu);
		//printf("dep[%d] = %d\n", u, vertex[u].dep);
		//printf("size[%d] = %d\n", u, vertex[u].size);
		for (int e = vertex[u].head; e; e = edge[e].next) {
			int v = edge[e].head;
			if (v == fu) continue;
			DFS1(v, u);
			vertex[u].size += vertex[v].size;
			if (vertex[vertex[u].hson].size < vertex[v].size) {
				vertex[u].hson = v;
			}
		}
		return;
	}

	int dfn;

	void DFS2(int u, int top) {
		dfn++;
		vertex[u].dfn = dfn;
		vertex[u].top = top;
		b[dfn] = a[u];
		//printf("vertex[%d].dfn = %d\n", u, vertex[u].dfn);
		//printf("vertex[%d].top = %d\n", u, vertex[u].top);
		//printf("vertex[%d].siz = %d\n", u, vertex[u].size);
		if (!vertex[u].hson) return;
		DFS2(vertex[u].hson, top);
		for (int e = vertex[u].head; e; e = edge[e].next) {
			int v = edge[e].head;
			if (v == vertex[u].fu) continue;
			if (v == vertex[u].hson) continue;
			DFS2(v, v);
		}
		return;
	}

	struct SegmentTree {
		struct Node {
			int val;
			int tag;
		} node[maxN * 4 + 10];

		void MakeTag(int u, int l, int r, int val) {
			node[u].val = (node[u].val + val * (r - l + 1) % p) % p;
			node[u].tag = (node[u].tag + val) % p;
			return;
		}

		void PushUp(int u) {
			node[u].val = (node[u * 2].val + node[u * 2 + 1].val) % p;
			return;
		}

		void PushDown(int u, int l, int r) {
			if (!node[u].tag) return;
			int mid = (l + r) / 2;
			MakeTag(u * 2, l, mid, node[u].tag);
			MakeTag(u * 2 + 1, mid + 1, r, node[u].tag);
			node[u].tag = 0;
			return;
		}

		void Build(int u, int l, int r) {
			if (l == r) {
				node[u].val = b[l] % p;
				return;
			}
			int mid = (l + r) / 2;
			Build(u * 2, l, mid);
			Build(u * 2 + 1, mid + 1, r);
			PushUp(u);
			return;
		}

		void Add(int u, int l, int r, int s, int t, int val) {
			if (s <= l && r <= t) {
				MakeTag(u, l, r, val);
				return;
			}
			PushDown(u, l, r);
			int mid = (l + r) / 2;
			if (s <= mid) Add(u * 2, l, mid, s, t, val);
			if (t >= mid + 1) Add(u * 2 + 1, mid + 1, r, s, t, val);
			PushUp(u);
			return;
		}

		int Ask(int u, int l, int r, int s, int t) {
			if (s <= l && r <= t) {
				return node[u].val;
			}
			PushDown(u, l, r);
			int mid = (l + r) / 2;
			if (t <= mid) return Ask(u * 2, l, mid, s, t);
			if (s >= mid + 1) return Ask(u * 2 + 1, mid + 1, r, s, t);
			return (Ask(u * 2, l, mid, s, t) + Ask(u * 2 + 1, mid + 1, r, s, t)) % p;
		}
	} SGT;

	void HeavyLightDecomposition() {
		DFS1(r, 0);
		DFS2(r, r);
		SGT.Build(1, 1, n);
		return;
	}

	void addPath(int u, int v, int val) {
		val %= p;
		while (vertex[u].top != vertex[v].top) {
			if (vertex[vertex[u].top].dep < vertex[vertex[v].top].dep) std::swap(u, v);
			SGT.Add(1, 1, n, vertex[vertex[u].top].dfn, vertex[u].dfn, val);
			u = vertex[vertex[u].top].fu;
		}
		if (vertex[u].dep > vertex[v].dep) std::swap(u, v);
		SGT.Add(1, 1, n, vertex[u].dfn, vertex[v].dfn, val);
		return;
	}

	void askPath(int u, int v) {
		int ret = 0;
		while (vertex[u].top != vertex[v].top) {
			if (vertex[vertex[u].top].dep < vertex[vertex[v].top].dep) std::swap(u, v);
			ret = (ret + SGT.Ask(1, 1, n, vertex[vertex[u].top].dfn, vertex[u].dfn)) % p;
			u = vertex[vertex[u].top].fu;
		}
		if (vertex[u].dep > vertex[v].dep) std::swap(u, v);
		ret = (ret + SGT.Ask(1, 1, n, vertex[u].dfn, vertex[v].dfn)) % p;
		std::cout << ret << '\n';
		return;
	}

	void addTree(int u, int val) {
		val %= p;
		SGT.Add(1, 1, n, vertex[u].dfn, vertex[u].dfn + vertex[u].size - 1, val);
		return;
	}

	void askTree(int u) {
		std::cout << SGT.Ask(1, 1, n, vertex[u].dfn, vertex[u].dfn + vertex[u].size - 1) << '\n';
		return;
	}
}

int main() {
	promote();
	std::cin >> n >> m >> r >> p;
	for (int i = 1; i <= n; i++) std::cin >> a[i];
	for (int i = 1; i <= n - 1; i++) {
		std::cin >> x >> y;
		graph::addEdge(x, y);
		graph::addEdge(y, x);
	}
	graph::HeavyLightDecomposition();
	for (int i = 1; i <= m; i++) {
		std::cin >> o;
		if (o == 1) {
			std::cin >> x >> y >> z;
			graph::addPath(x, y, z);
		} else if (o == 2) {
			std::cin >> x >> y;
			graph::askPath(x, y);
		} else if (o == 3) {
			std::cin >> x >> z;
			graph::addTree(x, z);
		} else if (o == 4) {
			std::cin >> x;
			graph::askTree(x);
		}
	}
	return 0;
}