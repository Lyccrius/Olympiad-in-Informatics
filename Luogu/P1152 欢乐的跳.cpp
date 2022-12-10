#include <cstdio>
#include <cmath>
#include <algorithm>

const int maxN = 1000 + 10;

int n;
int a[maxN];
int c[maxN];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	for (int i = 1; i < n; i++) c[i] = std::abs(a[i] - a[i - 1]);
	std::sort(c + 1, c + n);
	for (int i = 1; i < n; i++) if (c[i] != i) {printf("Not jolly\n"); return 0;}
	printf("Jolly\n");
	return 0;
}