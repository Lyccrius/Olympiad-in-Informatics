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

const int maxN = 150;
const int maxS = 70;
const int maxT = 1e6;

int n;
chr s[maxN + 10][maxS + 10];
chr t[maxT + 10];
int cnt[maxN + 10];
int top;

struct AhoCorasickAutomaton {
	struct Node {
		int son[30];
		int val;
		int fail;
		int index;
	} node[maxN * maxS + 10];

	int root;
	int ncnt;

	void Init() {
        //printf("initing\n");
		for (int i = 1; i <= n; i++) cnt[i] = 0;
		for (int i = 0; i <= ncnt; i++) {
			for (int j = 1; j <= 26; j++) node[i].son[j] = 0;
			node[i].val = 0;
			node[i].fail = 0;
			node[i].index = 0;
		}
		ncnt = 0;
        //printf("inited\n");
		return;
	}

	void Insert(chr *str, int i) {
		int u = root;
        //printf("inserted %s\n", str + 1);
		for (int i = 1; str[i]; i++) {
			if (node[u].son[str[i] - 'a' + 1] == 0) node[u].son[str[i] - 'a' + 1] = ++ncnt;
			u = node[u].son[str[i] - 'a' + 1];
			//printf("insert %d\n", u);
		}
		node[u].index = i;
		return;
	}

	void Build() {
		dic q;
		for (int i = 1; i <= 26; i++) if (node[root].son[i]) q.push_back(node[root].son[i]);
		while (!q.empty()) {
			int u = q.front();
			q.pop_front();
			//printf("build %d\n", u);
			for (int i = 1; i <= 26; i++) {
				if (node[u].son[i]) {
					node[node[u].son[i]].fail = node[node[u].fail].son[i];
					q.push_back(node[u].son[i]);
				} else {
					node[u].son[i] = node[node[u].fail].son[i];
				}
			}
		}
        //printf("built\n");
		return;
	}

	int Query(chr *str) {
		int ret = 0;
		int u = root;
		for (int i = 1; str[i]; i++) {
			u = node[u].son[str[i] - 'a' + 1];
			for (int j = u; j; j = node[j].fail) node[j].val++;
		}
		for (int i = 0; i <= ncnt; i++) {
			if (!node[i].index) continue;
			ret = std::max(ret, node[i].val);
			cnt[node[i].index] = node[i].val;
		}
		return ret;
	}
} ACM;

void mian() {
	ACM.Init();
	for (int i = 1; i <= n; i++) {
        //printf("%d / %d\n", i, n);
		std::cin >> (s[i] + 1);
        //printf("scaned %s\n", s[i] + 1);
		ACM.Insert(s[i], i);
	}
	ACM.Build();
	std::cin >> (t + 1);
	std::cout << (top = ACM.Query(t)) << '\n';
	for (int i = 1; i <= n; i++) {
		if (cnt[i] == top) {
			std::cout << (s[i] + 1) << '\n';
		}
	}
	return;
}

int main() {
    promote();
	while (std::cin >> n && n) mian();
	return 0;
}