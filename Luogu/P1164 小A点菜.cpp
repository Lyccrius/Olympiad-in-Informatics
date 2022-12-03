#include <cstdio>
#include <algorithm>

const int maxN = 100 + 10;
const int maxM = 10000 + 10;

int N, M;
int a[maxN];
int f[maxM];

int main() {
	scanf("%d%d", &N, &M);
	f[0] = 1;
	for (int i = 1; i <= N; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= N; i++) for (int j = M; j >= a[i]; j--) f[j] += f[j - a[i]];
	printf("%d\n", f[M]);
	return 0;
}