#include <iostream>
#include <algorithm>
#include <string>
#include <deque>

void promote() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	return;
}

typedef std::string str;
typedef std::deque<int> dic;

const int maxN = 1000;

int n;
str m;
int s;
int t;

namespace graph {
	struct Vertex {
		dic edge;
		int i;
		int o;
	} vertex[maxN + 10];

	struct Edge {
		int tail;
		int head;
		str text;
	};

	std::deque<Edge> edges;

	struct DisjointSetUnion {
		struct Node {
			int fa;
		} node[30];

		void Init() {
			for (int i = 1; i <= 26; i++) node[i].fa = i;
			return;
		}

		int Find(int u) {
			if (node[u].fa == u) return u;
			return node[u].fa = Find(node[u].fa);
		}

		void Union(int u, int v) {
			u = Find(u);
			v = Find(v);
			if (u == v) return;
			node[u].fa = v;
			return;
		}
	} DSU;

	void addEdge(int tail, int head, str text) {
		edges.push_back((Edge) {tail, head, text});
		vertex[tail].edge.push_back(edges.size() - 1);
		vertex[tail].o++;
		vertex[head].i++;
		DSU.Union(tail, head);
		return;
	}

    bool cmp(const int &a, const int &b) {
        return edges[a].text < edges[b].text;
    }

	struct Node {
		int u;
		int e;
	};

	dic s;

	void DFS(int u, int fe) {
        //printf("DFS %c ", u + 'a' - 1); if (~fe) std::cout << edges[fe].text; printf("\n");
		//printf("DFS %d from %d\n", u, fe);
		while (!vertex[u].edge.empty()) {
			int e = vertex[u].edge.front();
			int v = edges[e].head;
			vertex[u].edge.pop_front();
			DFS(v, e);
		}
		if (~fe) s.push_back(fe);
        //if (~fe) printf("s.push "), std::cout << edges[fe].text, printf("\n");
        //printf("DFS %c ", u + 'a' - 1); if (~fe) std::cout << edges[fe].text; printf(" end \n");
		return;
	}

	void print() {
        if (!s.empty()) std::cout << edges[s.back()].text, s.pop_back();
		while (!s.empty()) {
            std::cout << '.';
			std::cout << edges[s.back()].text;
			s.pop_back();
		}
		return;
	}
}

int abs(int x) {
	if (x < 0) x = - x;
	return x;
}

int main() {
	std::cin >> n;
    graph::DSU.Init();
	for (int i = 1; i <= n; i++) {
		std::cin >> m;
		int u = m.front() - 'a' + 1;
		int v = m.back() - 'a' + 1;
		graph::addEdge(u, v, m);
	}
	for (int i = 1; i <= 26; i++) {
		int d = graph::vertex[i].i - graph::vertex[i].o;
		if (abs(d) > 1) {
			std::cout << "***" << '\n';
			return 0;
		}
		if (d == - 1) {
			if (s) {
				std::cout << "***" << '\n';
				return 0;
			}
			s = i;
		}
		if (d == 1) {
			if (t) {
				std::cout << "***" << '\n';
				return 0;
			}
			t = i;
		}
	}
	if (s == 0) for (int i = 1; i <= 26; i++) if (graph::vertex[i].o && t != i) {s = i; break;}
	for (int i = 1; i <= 26; i++) std::sort(graph::vertex[i].edge.begin(), graph::vertex[i].edge.end(), graph::cmp);
	for (int i = 1; i <= 26; i++) {
		if (graph::vertex[i].i == 0 && graph::vertex[i].o == 0) continue;
		for (int j = i + 1; j <= 26; j++) {
			if (graph::vertex[j].i == 0 && graph::vertex[j].o == 0) continue;
			if (graph::DSU.Find(i) != graph::DSU.Find(j)) {
				std::cout << "***" << '\n';
				return 0;
			}
		}
	}
	graph::DFS(s, - 1);
	graph::print();
	return 0;
}