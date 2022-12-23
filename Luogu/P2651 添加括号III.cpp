#include <cstdio>

const int maxN = 1e5 + 10;

int t;
int n;
int a[maxN];

int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

void mian() {
	bool ok = false;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 3; i <= n; i++) {
		int g = gcd(a[2], a[i]);
		if (g != 1) a[2] /= g;
		if (a[2] == 1) {
			ok = true;
			break;
		}
	}
	if (a[1] % a[2] == 0) ok = true;
	if (ok) printf("Yes\n");
	else printf("No\n");
	return;
}

int main() {
	scanf("%d", &t);
	while (t--) mian();
	return 0;
}