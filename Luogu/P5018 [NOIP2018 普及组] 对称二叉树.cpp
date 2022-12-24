#include <cstdio>
#include <algorithm>

const int maxN = 1e6 + 10;

int n;
int ans;

struct Tree {
	struct Node {
		int v;
		int l;
		int r;
	} node[maxN];

	bool check(int x, int y) {
		if (x == -1 && y == -1) return true;
		if (x == -1 || y == -1) return false;
		if (node[x].v != node[y].v) return false;
		return check(node[x].l, node[y].r) && check(node[y].l, node[x].r);
	}

	int count(int x) {
		if (x == -1) return 0;
		return count(node[x].l) + count(node[x].r) + 1;
	}
} tree;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &tree.node[i].v);
	for (int i = 1; i <= n; i++) scanf("%d%d", &tree.node[i].l, &tree.node[i].r);
	for (int i = 1; i <= n; i++) if (tree.check(tree.node[i].l, tree.node[i].r)) ans = std::max(ans, tree.count(i));
	printf("%d\n", ans);
	return 0;
}