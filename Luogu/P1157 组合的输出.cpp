#include <cstdio>

const int maxN = 21 + 10;

int n, r;
int used[maxN];

void DFS(int cur, int head) {
	if (cur > r) {
		for (int i = 1; i <= r; i++) printf("%3d", used[i]);
		printf("\n");
		return;
	}
	if (head > n) return;
	for (int i = head; i <= n; i++) {
		used[cur] = i;
		DFS(cur + 1, i + 1);
	}
	return;
}

int main() {
	scanf("%d%d", &n, &r);
	DFS(1, 1);
	return 0;
}