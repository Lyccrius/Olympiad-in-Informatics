#include <cstdio>

const int maxN = 1e5 + 10;
const int maxM = 1e5 + 10;

int n;
int a[maxN];
int m;
int l[maxN], r[maxN];

int pre[maxN];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) scanf("%d%d", &l[i], &r[i]);
	for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + a[i];
	for (int i = 1; i <= m; i++) printf("%d\n", pre[r[i]] - pre[l[i] - 1]);
	return 0;
}