#include <cstdio>

const int maxN = 1e5 + 10;

int N;
int Next[maxN];
int dep[maxN];
int onc[maxN];
int res[maxN];
int vis[maxN];

void Circ(int x, int num) {
	while (!onc[x]) {
		res[x] = num;
		onc[x] = true;
		x = Next[x];
	}
	return;
}

void DFS(int x, int depth) {
	if (res[x]) return;
	if (vis[x]) {
		Circ(x, depth - dep[x]);
		return;
	}
	dep[x] = depth;
	vis[x] = true;
	DFS(Next[x], dep[x] + 1);
	vis[x] = false;
	if (!onc[x]) res[x] = res[Next[x]] + 1;
	return;
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) scanf("%d", &Next[i]);
	for (int i = 1; i <= N; i++) {
		DFS(i, 1);
		printf("%d\n", res[i]);
	}
	return 0;
}