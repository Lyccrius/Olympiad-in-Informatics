#include <cstdio>

const int maxN = 3000 + 10;

int x, y;
int res[maxN];
int cnt;

bool check(int x) {
	if (x % 400 == 0) return true;
	if (x % 4 == 0 && x % 100 != 0) return true;
	return false;
}

int main() {
	scanf("%d%d", &x, &y);
	for (int i = x; i <= y; i++) if (check(i)) res[++cnt] = i;
	printf("%d\n", cnt);
	for (int i = 1; i <= cnt; i++) printf("%d ", res[i]);
    printf("\n");
	return 0;
}