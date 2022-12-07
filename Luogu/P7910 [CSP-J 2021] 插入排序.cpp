#include <cstdio>

const int maxN = 8000 + 10;

int n, Q;
int a[maxN];
int rank[maxN];

int main() {
	scanf("%d%d", &n, &Q);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) rank[i] = 1;
	for (int i = 1; i <= n; i++) for (int j = 1; j < i; j++) if (a[j] <= a[i]) rank[i]++; else rank[j]++;
	while (Q--) {
		int opt, x, v;
		scanf("%d", &opt);
		if (opt == 1) {
			scanf("%d%d", &x, &v);
			for (int i = 1; i < x; i++) {
				if (a[i] <= a[x] && a[i] > v) rank[i]++, rank[x]--;
				if (a[i] > a[x] && a[i] <= v) rank[i]--, rank[x]++;
			}
			for (int i = x + 1; i <= n; i++) {
				if (a[i] < a[x] && a[i] >= v) rank[i]++, rank[x]--;
				if (a[i] >= a[x] && a[i] < v) rank[i]--, rank[x]++;
			}
			a[x] = v;
		} else {
			scanf("%d", &x);
			printf("%d\n", rank[x]);
		}
	}
	return 0;
}