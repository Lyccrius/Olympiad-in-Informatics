#include <iostream>
#include <vector>
#include <deque>

void promote() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	return;
}

typedef char chr;
typedef std::vector<int> vic;
typedef std::deque<int> diq;

const int maxN = 200;
const int maxM = 1e6;

int n;
chr s[maxM + 10];
int ans[maxN + 10];

struct AhoCosarickAutomaton {
	struct Node {
		int val;
		int son[26 + 10];
		int fail;
		int head;
		vic index;
	} node[maxM + 10];

	struct Edge {
		int head;
		int next;
	} edge[maxM + 10];

	int root;
	int ncnt;
	int ecnt;

	void Insert(chr *str, int i) {
		int u = root;
		for (int i = 1; str[i]; i++) {
			if (node[u].son[str[i] - 'a' + 1] == 0) node[u].son[str[i] - 'a' + 1] = ++ncnt;
			u = node[u].son[str[i] - 'a' + 1];
			node[u].val++;
		}
		node[u].index.push_back(i);
		return;
	}

	void Build() {
		diq q;
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

	void addEdge(int tail, int head) {
		ecnt++;
		edge[ecnt].head = head;
		edge[ecnt].next = node[tail].head;
		node[tail].head = ecnt;
		return;
	}

	void BuildFailTree() {
		for (int u = 1; u <= ncnt; u++) addEdge(node[u].fail, u);
		return;
	}

	void DFS(int u) {
		for (int e = node[u].head; e; e = edge[e].next) {
			int v = edge[e].head;
			DFS(v);
			node[u].val += node[v].val;
		}
		for (auto i : node[u].index) {
			ans[i] = node[u].val;
		}
	}
} ACM;

int main() {
	promote();
	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> (s + 1);
		ACM.Insert(s, i);
	}
	ACM.Build();
	ACM.BuildFailTree();
	ACM.DFS(ACM.root);
	for (int i = 1; i <= n; i++) std::cout << ans[i] << '\n';
	return 0;
}