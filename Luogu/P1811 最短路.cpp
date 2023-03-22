#include <iostream>
#include <deque>
#include <map>

const int maxN = 3000;
const int maxM = 20000;
const int maxK = 1e5;
const int inf = 1e9 + 10;

int n, m, k;
int x, y;
int a, b, c;

namespace graph {
	struct Vertex {
		int head;
	} vertex[maxN + 10];

	struct Edge {
		int tail;
		int head;
		int next;
		int from;
		int vis;
	} edge[maxM * 2 + 10];

	int ecnt;

	void addEdge(int tail, int head) {
		ecnt++;
		edge[ecnt].tail = tail;
		edge[ecnt].head = head;
		edge[ecnt].next = vertex[tail].head;
		vertex[tail].head = ecnt;
		return;
	}

	struct Curse {
		int a, b, c;

		bool operator<(const Curse &other) const {
			if (a != other.a) return a < other.a;
			if (b != other.b) return b < other.b;
			return c < other.c;
		}
	};

	std::map<Curse, bool> curse;

	void addCurse(int a, int b, int c) {
		curse[(Curse) {a, b, c}] = true;
		return;
	}

	struct Node {
		int e;
		int from;
		int u;
		int dis;
	};

	bool vis[maxN + 10][maxN + 10];

	void print(int e) {
		if (e == 0) return;
		print(edge[e].from);
		std::cout << edge[e].tail << ' ';
		return;
	}

	void BFS() {
		std::deque<Node> q;
		q.push_back((Node) {0, 0, 1, 0});
		while (q.size()) {
			int fe = q.front().e;
			int fa = q.front().from;
			int u = q.front().u;
			int dis = q.front().dis;
			q.pop_front();
			for (int e = vertex[u].head; e; e = edge[e].next) {
				int v = edge[e].head;
				if (edge[e].vis) continue;
				if (curse[(Curse) {fa, u, v}]) continue;
				edge[e].vis = true;
				edge[e].from = fe;
				q.push_back((Node) {e, u, v, dis + 1});
				if (v == n) {
					std::cout << dis + 1 << '\n';
					print(e);
					std::cout << n << '\n';
					return;
				}
			}
		}
		std::cout << - 1 << '\n';
		return;
	}
}

int main() {
	std::cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) graph::vertex[i].head = 0;
	for (int i = 1; i <= m; i++) {
		std::cin >> x >> y;
		graph::addEdge(x, y);
		graph::addEdge(y, x);
	}
	for (int i = 1; i <= k; i++) {
		std::cin >> a >> b >> c;
		graph::addCurse(a, b, c);
	}
	graph::BFS();
	return 0;
}