#include <cstdio>
#include <algorithm>

const int maxN = 999 + 10;
const int maxM = 2000000 + 10;

int n, m;
int a[maxM];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d", &a[i]);
	std::sort(a + 1, a + m + 1);
	for (int i = 1; i <= m; i++) printf("%d ", a[i]);
	printf("\n");
	return 0;
}