#include <iostream>
#include <deque>

void promote() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	return;
}

typedef char chr;
typedef std::deque<int> dic;

const int maxN = 1e6;
const int maxS = 1e6;
const int maxT = 1e6;

int n;
chr s[maxS + 10];
chr t[maxT + 10];

struct AhoCorasickAutomaton {
	struct Node {
		int son[30];
		int end;
		int fail;
	} node[maxN + 10];

	int root;
	int ncnt;

	void Insert(chr *str) {
		int u = root;
		for (int i = 1; str[i]; i++) {
			if (node[u].son[str[i] - 'a' + 1] == 0) node[u].son[str[i] - 'a' + 1] = ++ncnt;
			u = node[u].son[str[i] - 'a' + 1];
		}
		node[u].end++;
		return;
	}

	void Build() {
		dic q;
		for (int i = 1; i <= 26; i++) if (node[root].son[i]) q.push_back(node[root].son[i]);
		while (!q.empty()) {
			int u = q.front();
			q.pop_front();
			for (int i = 1; i <= 26; i++) {
				if (node[u].son[i]) {
					node[node[u].son[i]].fail = node[node[u].fail].son[i];
					q.push_back(node[u].son[i]);
				} else {
					node[u].son[i] = node[node[u].fail].son[i];
				}
			}
		}
		return;
	}

	int Query(chr *str) {
		int ret = 0;
		int u = root;
		for (int i = 1; str[i]; i++) {
			u = node[u].son[str[i] - 'a' + 1];
			for (int j = u; j && ~node[j].end; j = node[j].fail) {
				ret += node[j].end;
				node[j].end = - 1;
			}
		}
		return ret;
	}
} ACM;

int main() {
	promote();
	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> (s + 1);
		ACM.Insert(s);
	}
	ACM.Build();
	std::cin >> (t + 1);
	std::cout << ACM.Query(t);
	return 0;
}