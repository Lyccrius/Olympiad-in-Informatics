#include <cstdio>

int t;
int a, b, c, d;

void mian() {
	scanf("%d%d%d%d", &a, &b, &c, &d);
	bool ok = false;
	if (a < b && c < d && a < c && b < d) ok = true;
	if (c < a && d < b && c < d && a < b) ok = true;
	if (d < c && b < a && d < b && c < a) ok = true;
	if (b < d && a < c && b < a && d < c) ok = true;
	if (ok) printf("YES\n");
	else printf("NO\n");
	return;
}

int main() {
	scanf("%d", &t);
	while (t--) mian();
	return 0;
}