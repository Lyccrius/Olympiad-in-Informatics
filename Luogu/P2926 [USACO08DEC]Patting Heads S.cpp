#include <cstdio>

const int maxN = 1e5 + 10;
const int maxA = 1e6 + 10;

int N;
int A[maxN];
int cnt[maxA];
int sum[maxA];

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &A[i]);
		cnt[A[i]]++;
	}
	for (int i = 1; i < maxA; i++) for (int j = i; j < maxA; j += i) sum[j] += cnt[i];
	for (int i = 1; i <= N; i++) printf("%d\n", sum[A[i]] - 1);
    return 0;
}