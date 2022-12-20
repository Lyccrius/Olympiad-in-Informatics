#include <cstdio>

const int maxK = 40 + 10;
const int inf = 1e9 + 10;

int t;
int k, n;
int a[maxK];

void mian() {
	scanf("%d%d", &k, &n);
	for (int i = k; i >= 1; i--) a[i] = n - k + i;
	a[k + 1] = inf;
	int dif = 1;
	for (int i = 1; i <= k; i++) {
		if (a[i - 1] + dif < a[i + 1] && a[i - 1] + dif <= n) {
			a[i] = a[i - 1] + dif;
			dif++;
		} else {
			a[i] = a[i - 1] + 1;
		}
	}
	for (int i = 1; i <= k; i++) printf("%d ", a[i]);
	printf("\n");
	return;
}

int main() {
	scanf("%d", &t);
	while (t--) mian();
	return 0;
}