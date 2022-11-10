#include <cstdio>

const int maxn = 100 + 10;

int n;
int degree[maxn];

int main() {
	scanf("%d", &n);
	for (int i = n; i >= 0; i--) scanf("%d", &degree[i]);
	for (int i = n; i >= 0; i--) {
		if (degree[i] == 0) continue;
		if (degree[i] > 0 && i != n) printf("+");
		if (degree[i] > 0 && degree[i] != 1) printf("%d", degree[i]);
		if (degree[i] == -1 && i) printf("-");
		if (degree[i] == -1 && !i) printf("-1");
		if (degree[i] < -1) printf("%d", degree[i]);
		if (degree[i] == 1 && !i) printf("1");
		if (i != 0) printf("x");
		if (i != 0 && i != 1) printf("^%d", i);
	}
	return 0;
}