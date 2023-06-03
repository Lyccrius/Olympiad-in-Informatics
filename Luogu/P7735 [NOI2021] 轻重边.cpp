#include <iostream>

void promote() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	return;
}

const int maxN = 1e5;
const int maxM = 1e5;

int T;
int n, m;
int u, v;
int op, a, b;

struct SegmentTree {
	struct Node {
		int l, r;
		int res;
		int tag;
	} node[4 * maxN + 10], en;

	Node Merge(Node a, Node b) {
		Node ret = en;
		ret.l = a.l;
		ret.r = b.r;
		ret.res = a.res + b.res + ((a.r == b.l) && (a.r || b.l));
		return ret;
	}

	void PushUp(int u) {
		node[u] = Merge(node[2 * u], node[2 * u + 1]);
		return;
	}

	void MakeTag(int u, int l, int r, int val) {
		node[u].l = val;
		node[u].r = val;
		node[u].res = r - l;
		node[u].tag = val;
		return;
	}

	void PushDown(int u, int l, int r) {
		if (!node[u].tag) return;
		int mid = (l + r) / 2;
		MakeTag(2 * u, l, mid, node[u].tag);
		MakeTag(2 * u + 1, mid + 1, r, node[u].tag);
		node[u].tag = 0;
		return;
	}

	void Build(int u, int l, int r) {
		if (l == r) {
			node[u].l = 0;
			node[u].r = 0;
			node[u].res = 0;
			node[u].tag = 0;
			return;
		}
		int mid = (l + r) / 2;
		Build(2 * u, l, mid);
		Build(2 * u + 1, mid + 1, r);
		PushUp(u);
		return;
	}

	void Modify(int u, int l, int r, int s, int t, int val) {
		if (s <= l && r <= t) {
			MakeTag(u, l, r, val);
			return;
		}
		PushDown(u, l, r);
		int mid = (l + r) / 2;
		if (s <= mid) Modify(2 * u, l, mid, s, t, val);
		if (t >= mid + 1) Modify(2 * u + 1, mid + 1, r, s, t, val);
		PushUp(u);
		return;
	}

	Node Query(int u, int l, int r, int s, int t) {
		if (s <= l && r <= t) return node[u];
		PushDown(u, l, r);
		int mid = (l + r) / 2;
		if (t <= mid) return Query(2 * u, l, mid, s, t);
		if (s >= mid + 1) return Query(2 * u + 1, mid + 1, r, s, t);
		return Merge(Query(2 * u, l, mid, s, t), Query(2 * u + 1, mid + 1, r, s, t));
	}

	int Query(int u, int l, int r, int pos) {
		if (l == r) return node[u].r;
		PushDown(u, l, r);
		int mid = (l + r) / 2;
		if (pos <= mid) return Query(2 * u, l, mid, pos);
		if (pos >= mid + 1) return Query(2 * u + 1, mid + 1, r, pos);
	}
} SGT;

namespace graph {
	struct Vertex {
		int head;
		int hson;
		int size;
		int dep;
		int dfn;
		int top;
		int fa;
	} vertex[maxN + 10], ev;

	struct Edge {
		int head;
		int next;
	} edge[2 * maxN + 10];

	int ecnt;
	int dfn;
	int t;

	void addEdge(int tail, int head) {
		ecnt++;
		edge[ecnt].head = head;
		edge[ecnt].next = vertex[tail].head;
		vertex[tail].head = ecnt;
		return;
	}

	void clear() {
		for (int i = 1; i <= n; i++) vertex[i] = ev;
		ecnt = 0;
		dfn = 0;
		t = 0;
		return;
	}

	void DFS0(int u, int from) {
		vertex[u].size = 1;
		vertex[u].dep = vertex[from].dep + 1;
		for (int e = vertex[u].head; e; e = edge[e].next) {
			int v = edge[e].head;
			if (v == from) continue;
			DFS0(v, u);
			vertex[u].size += vertex[v].size;
			if (vertex[v].size > vertex[vertex[u].hson].size) vertex[u].hson = v;
		}
		return;
	}

	void DFS1(int u, int from, int top) {
		dfn++;
		vertex[u].dfn = dfn;
		vertex[u].top = top;
		vertex[u].fa = from;
		if (vertex[u].hson) DFS1(vertex[u].hson, u, top);
		for (int e = vertex[u].head; e; e = edge[e].next) {
			int v = edge[e].head;
			if (v == from) continue;
			if (v == vertex[u].hson) continue;
			DFS1(v, u, v);
		}
		return;
	}

	void modify(int u, int v) {
		t++;
		while (vertex[u].top != vertex[v].top) {
			if (vertex[vertex[u].top].dep < vertex[vertex[v].top].dep) std::swap(u, v);
			SGT.Modify(1, 1, n, vertex[vertex[u].top].dfn, vertex[u].dfn, t);
			u = vertex[vertex[u].top].fa;
		}
		if (vertex[u].dep > vertex[v].dep) std::swap(u, v);
		SGT.Modify(1, 1, n, vertex[u].dfn, vertex[v].dfn, t);
		return;
	}

	void query(int u, int v) {
		int res = 0;
		while (vertex[u].top != vertex[v].top) {
			if (vertex[vertex[u].top].dep < vertex[vertex[v].top].dep) std::swap(u, v);
			res += SGT.Query(1, 1, n, vertex[vertex[u].top].dfn, vertex[u].dfn).res;
			int f = SGT.Query(1, 1, n, vertex[vertex[vertex[u].top].fa].dfn);
			int g = SGT.Query(1, 1, n, vertex[vertex[u].top].dfn);
			res += (f == g) && (f || g);
			u = vertex[vertex[u].top].fa;
		}
		if (vertex[u].dep > vertex[v].dep) std::swap(u, v);
		res += SGT.Query(1, 1, n, vertex[u].dfn, vertex[v].dfn).res;
		std::cout << res << '\n';
		return;
	}
}

void mian() {
	graph::clear();
	std::cin >> n >> m;
	SGT.Build(1, 1, n);
	for (int i = 1; i <= n - 1; i++) std::cin >> u >> v, graph::addEdge(u, v), graph::addEdge(v, u);
	graph::DFS0(1, 0);
	graph::DFS1(1, 0, 1);
	for (int i = 1; i <= m; i++) {
		std::cin >> op >> a >> b;
		if (op == 1) graph::modify(a, b);
		if (op == 2) graph::query(a, b);
	}
	return;
}

int main() {
	promote();
	std::cin >> T;
	while (T--) mian();
	return 0;
}