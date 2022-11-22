#include <cstdio>

const int maxN = 2e5 + 10;

int t;
int n;
int a[maxN];

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) scanf("%d", &a[i]);
		int gu = 0;
		while (a[gu] >= a[gu + 1]) gu++;
		bool ok = true;
		for (int i = gu; i < n - 1; i++) {
			if (a[i] > a[i + 1]) {
				ok = false;
				break;
			}
		}
		if (ok) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}