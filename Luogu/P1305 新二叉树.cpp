#include <cstdio>

const int maxN = 26 + 10;

int n;
char str[5];

namespace Graph {
	struct Vertex {
		int left;
		int right;
	} vertex[maxN];
	int root;

	void DFS(int x) {
		if (x == 0) return;
		printf("%c", x - 1 + 'a');
		DFS(vertex[x].left);
		DFS(vertex[x].right);
		return;
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%s", str + 1);
		if (i == 1) Graph::root = str[1] - 'a' + 1;
		if (str[2] != '*') Graph::vertex[str[1] - 'a' + 1].left = str[2] - 'a' + 1;
		if (str[3] != '*') Graph::vertex[str[1] - 'a' + 1].right = str[3] - 'a' + 1;
	}
	Graph::DFS(Graph::root);
	return 0;
}