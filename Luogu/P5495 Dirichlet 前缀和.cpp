#include <cstdio>

typedef unsigned int unt;

const unt maxN = 2e7 + 10;

unt n, seed;
unt a[maxN];
bool vis[maxN];
unt ans;

unt getNext() {
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}

int main() {
	scanf("%u%u", &n, &seed);
	for (unt i = 1; i <= n; i++) a[i] = getNext();
	vis[1] = true;
	for (unt i = 2; i <= n; i++) if (!vis[i]) for (unt j = 1, k = 1; i * j <= n; j++, k++) a[i * j] += a[k], vis[i * j] = true;
	for (unt i = 1; i <= n; i++) ans ^= a[i];
	printf("%u\n", ans);
	return 0;
}