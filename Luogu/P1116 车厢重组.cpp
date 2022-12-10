#include <cstdio>

const int maxN = 10000 + 10;

int N;
int A[maxN];
int cnt;

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) scanf("%d", &A[i]);
	for (int i = 1; i <= N; i++) for (int j = 1; j < i; j++) if (A[i] < A[j]) cnt++;
	printf("%d\n", cnt);
	return 0;
}