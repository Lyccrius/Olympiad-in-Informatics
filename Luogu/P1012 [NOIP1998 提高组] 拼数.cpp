#include <cstdio>
#include <algorithm>

const int maxN = 20 + 10;

int n;
int a[maxN];

bool cmp(long long a, long long b) {
	int sizeA = 10;
	int sizeB = 10;
	while (a / sizeA) sizeA *= 10;
	while (b / sizeB) sizeB *= 10;
	long long resA = a * sizeB + b;
	long long resB = b * sizeA + a;
	return resA > resB;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	std::sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= n; i++) printf("%d", a[i]);
	printf("\n");
	return 0;
}