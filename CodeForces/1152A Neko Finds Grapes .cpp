#include <cstdio>
#include <algorithm>

const int maxN = 1e5 + 10;
const int maxM = 1e5 + 10;

int n, m;
int a[maxN];
int b[maxM];
int cntOddA;
int cntEvenA;
int cntOddB;
int cntEvenB;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= m; i++) scanf("%d", &b[i]);
	for (int i = 1; i <= n; i++) if (a[i] % 2) cntOddA++; else cntEvenA++;
	for (int i = 1; i <= m; i++) if (b[i] % 2) cntOddB++; else cntEvenB++;
	printf("%d\n", std::min(cntOddA, cntEvenB) + std::min(cntOddB, cntEvenA));
	return 0;
}