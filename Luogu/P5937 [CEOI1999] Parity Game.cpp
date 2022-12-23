#include <cstdio>
#include <algorithm>

const int maxM = 5e3 + 10;

int n, m;
int l[maxM], r[maxM], ans[maxM];
char str[10];

struct DisjointSetUnion {
	struct Node {
		int fa;
		int dis;
	} node[maxM << 1];

	void Init() {
		for (int i = 1; i <= n; i++) node[i].fa = i;
		return;
	}

	int Get(int u) {
		if (u == node[u].fa) return u;
		int v = Get(node[u].fa);
		node[u].dis ^= node[node[u].fa].dis;
		node[u].fa = v;
		return v;
	}
} DSU;

void Discrete() {
	int range[maxM << 1];
	int head = 0;
	for (int i = 1; i <= m; i++) {
		range[++head] = l[i] - 1;
		range[++head] = r[i];
	}
	std::sort(range + 1, range + head + 1);
	head = std::unique(range + 1, range + head + 1) - range - 1;
	for (int i = 1; i <= m; i++) {
		l[i] = std::lower_bound(range + 1, range + head + 1, l[i] - 1) - range;
		r[i] = std::lower_bound(range + 1, range + head + 1, r[i]) - range;
	}
	n = head;
	return;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d%d%s", &l[i], &r[i], str), ans[i] = (str[0] == 'o');
	Discrete();
	DSU.Init();
	for (int i = 1; i <= m; i++) {
		int u = DSU.Get(l[i]);
		int v = DSU.Get(r[i]);
		if (u == v) {
			if ((DSU.node[l[i]].dis ^ DSU.node[r[i]].dis) != ans[i]) {
				printf("%d\n", i - 1);
				return 0;
			}
		} else {
			DSU.node[u].fa = v;
			DSU.node[u].dis = DSU.node[l[i]].dis ^ DSU.node[r[i]].dis ^ ans[i];
		}
	}
	printf("%d\n", m);
	return 0;
}