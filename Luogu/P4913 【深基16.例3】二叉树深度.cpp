#include <cstdio>
#include <algorithm>

const int maxN = 1e6 + 10;

int n;

struct Tree {
	struct Node {
		int depth;
		int lNode;
		int rNode;
	} node[maxN];

	int DFS(int xNode, int depth) {
		if (xNode == 0) return 0;
		node[xNode].depth = depth;
		int ret = depth;
		ret = std::max(ret, DFS(node[xNode].lNode, depth + 1));
		ret = std::max(ret, DFS(node[xNode].rNode, depth + 1));
		return ret;
	}
} tree;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &tree.node[i].lNode, &tree.node[i].rNode);
	printf("%d\n", tree.DFS(1, 1));
	return 0;
}