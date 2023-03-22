#include <iostream>

typedef char chr;

const int maxN = 1e6;

const int _and = 1;
const int _or = 2;
const int _xor = 3;
const int _not = 4;
const int _in = 5;

int n;
chr s[5];
int u, v;

namespace graph {
	struct Vertex {
		int head;
		int type;
		int lson;
		int rson;
		int val;
		int deg;
		int tag;
	} vertex[maxN + 10];

	int root;

	void DFS(int u) {
		int l = vertex[u].lson;
		int r = vertex[u].rson;
		if (l) DFS(l);
		if (r) DFS(r);
		if (vertex[u].type == _and) {
			vertex[u].val = vertex[l].val & vertex[r].val;
		}
		if (vertex[u].type == _or) {
			vertex[u].val = vertex[l].val | vertex[r].val;
		}
		if (vertex[u].type == _xor) {
			vertex[u].val = vertex[l].val ^ vertex[r].val;
		}
		if (vertex[u].type == _not) {
			vertex[u].val = ! vertex[l].val;
		}
		return;
	}

	void DP(int u) {
		int l = vertex[u].lson;
		int r = vertex[u].rson;
		if (vertex[u].tag) {
			if (l) {
				vertex[l].tag = true;
				DP(l);
			}
			if (r) {
				vertex[r].tag = true;
				DP(r);
			}
			return;
		}
		if (vertex[u].type == _and) {
			if (vertex[l].val == true && vertex[r].val == false) {
				vertex[l].tag = true;
			}
			if (vertex[r].val == true && vertex[l].val == false) {
				vertex[r].tag = true;
			}
			if (vertex[l].val == false && vertex[r].val == false) {
				vertex[l].tag = true;
				vertex[r].tag = true;
			}
		}
		if (vertex[u].type == _or) {
			if (vertex[l].val == false && vertex[r].val == true) {
				vertex[l].tag = true;
			}
			if (vertex[r].val == false && vertex[l].val == true) {
				vertex[r].tag = true;
			}
			if (vertex[l].val == true && vertex[r].val == true) {
				vertex[l].tag = true;
				vertex[r].tag = true;
			}
		}
		if (l) DP(l);
		if (r) DP(r);
		return;
	}

	void mian() {
		for (int i = 1; i <= n; i++) {
			if (vertex[i].deg == 0) {
				root = i;
			}
		}
		DFS(root);
		DP(root);
		for (int i = 1; i <= n; i++) {
			if (vertex[i].type == _in) {
				if (vertex[i].tag) {
					std::cout << vertex[root].val;
				} else {
					std::cout << ! vertex[root].val;
				}
			}
		}
		return;
	}
}

int main() {
	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> s;
		if (s[0] == 'A') {
			std::cin >> u >> v;
			graph::vertex[i].type = _and;
			graph::vertex[i].lson = u;
			graph::vertex[i].rson = v;
			graph::vertex[u].deg++;
			graph::vertex[v].deg++;
		}
		if (s[0] == 'O') {
			std::cin >> u >> v;
			graph::vertex[i].type = _or;
			graph::vertex[i].lson = u;
			graph::vertex[i].rson = v;
			graph::vertex[u].deg++;
			graph::vertex[v].deg++;
		}
		if (s[0] == 'X') {
			std::cin >> u >> v;
			graph::vertex[i].type = _xor;
			graph::vertex[i].lson = u;
			graph::vertex[i].rson = v;
			graph::vertex[u].deg++;
			graph::vertex[v].deg++;
		}
		if (s[0] == 'N') {
			std::cin >> u;
			graph::vertex[i].type = _not;
			graph::vertex[i].lson = u;
			graph::vertex[u].deg++;
		}
		if (s[0] == 'I') {
			std::cin >> graph::vertex[i].val;
			graph::vertex[i].type = _in;
		}
	}
	graph::mian();
	return 0;
}