#include <iostream>
#include <vector>
#include <cstring>

typedef char chr;
typedef std::vector<int> vic;

const int maxS = 2e5;
const int maxN = 2e5;
const int maxM = 2e5;

int t;
chr S[maxS + 10];
int s;
int na;
int la[maxN + 10], ra[maxN + 10];
int nb;
int lb[maxN + 10], rb[maxN + 10];
int m;
int x, y;

namespace graph {
	struct Vertex {
		int l, r;
		vic edge;
		int deg;
		int dfn;
		int ins;
		int res;
	} vertex[maxN + 10];

	struct Edge {
		int head;
	};
	
	std::vector<Edge> edge;

	void addEdge(int tail, int head) {
        //printf("%d %d\n", tail, head);
		edge.push_back((Edge) {head});
		vertex[tail].edge.push_back(edge.size() - 1);
		vertex[head].deg++;
		return;
	}

	int getlen(int l, int r) {
		if (l == 0 && r == 0) return 0;
		//printf("len [%d, %d] = %d\n", l, r, (r - l + 1));
		return (r - l + 1);
	}

	bool ispre(int b, int a) {
		int lb = getlen(vertex[b].l, vertex[b].r);
		int la = getlen(vertex[a].l, vertex[a].r);
		if (lb > la) return false;
		for (int i = 0; i < lb; i++) {
			if (S[vertex[b].l + i] != S[vertex[a].l + i]) {
				return false;
			}
		}
		return true;
	}

	void build() {
		for (int i = 1; i <= nb; i++) {
			for (int j = 1; j <= na; j++) {
				if (ispre(i + na, j)) {
					addEdge(i + na, j);
				}
			}
		}
		return;
	}

	int dfn;
	int ring;
	int ans;

	void Tarjan(int u) {
		dfn++;
		vertex[u].dfn = dfn;
		vertex[u].ins = true;
		vertex[u].res = 0;
		for (auto e : vertex[u].edge) {
			int v = edge[e].head;
			if (vertex[v].dfn) {
				if (vertex[v].ins) {
					ring = true;
				}
			} else {
				Tarjan(v);
			}
				vertex[u].res = std::max(vertex[u].res, vertex[v].res);
		}
		if (u <= na) vertex[u].res += getlen(vertex[u].l, vertex[u].r);
        vertex[u].ins = false;
		//printf("res[%d] = %d\n", u, vertex[u].res);
		ans = std::max(ans, vertex[u].res);
		return;
	}

	void mian() {
		for (int i = 1; i <= na + nb; i++) {
			if (!vertex[i].dfn) {
				Tarjan(i);
			}
		}
		if (ring) ans = - 1;
		std::cout << ans << '\n';
		return;
	}

	void init() {
		edge.clear();
		for (int i = 1; i <= na + nb; i++) {
			vertex[i].edge.clear();
			vertex[i].deg = 0;
			vertex[i].dfn = 0;
			vertex[i].ins = false;
			vertex[i].res = 0;
		}
		dfn = 0;
		ring = 0;
		ans = 0;
		return;
	}
}

void check(int &l, int &r) {
	if (l < 1) l = 0, r = 0;
	if (r > s) l = 0, r = 0;
	if (l > r) l = 0, r = 0;
	return;
}

void mian() {
	graph::init();
	std::cin >> (S + 1); s = std::strlen(S + 1);
	std::cin >> na;
	for (int i = 1; i <= na; i++) {
		std::cin >> la[i] >> ra[i];
		check(la[i], ra[i]);
		graph::vertex[i].l = la[i];
		graph::vertex[i].r = ra[i];
	}
	std::cin >> nb;
	for (int i = 1; i <= nb; i++) {
		std::cin >> lb[i] >> rb[i];
		check(lb[i], rb[i]);
		graph::vertex[i + na].l = lb[i];
		graph::vertex[i + na].r = rb[i];
	}
	std::cin >> m;
	for (int i = 1; i <= m; i++) {
		std::cin >> x >> y;
		graph::addEdge(x, y + na);
	}
	graph::build();
	graph::mian();
	return;
}

int main() {
	std::cin >> t;
	while (t--) mian();
	return 0;
}

/*
    abaaaba

1      aaba
2   aba

3     aa
*/