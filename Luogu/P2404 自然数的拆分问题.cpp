#include <cstdio>

const int maxN = 8 + 10;

int n;
int a[maxN];

void print(int dep) {
	for (int i = 1; i < dep; i++) printf("%d+", a[i]);
	printf("%d\n", a[dep]);
	return;
}

void DFS(int now, int dep) {
	for (int i = a[dep - 1]; i <= now; i++) if (i < n) {
		a[dep] = i;
		now -= i;
		if (now == 0) print(dep);
		else DFS(now, dep + 1);
		now += i;
	}
	return;
}

int main() {
	scanf("%d", &n);
	a[0] = 1;
	DFS(n, 1);
	return 0;
}