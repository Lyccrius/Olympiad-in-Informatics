#include <cstdio>

const int maxN = 1e6 + 10;

int N, Q;
long long A[maxN];
int op, i, x;
int cnt[maxN];
int to, rp;

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) scanf("%lld", &A[i]);
	scanf("%d", &Q);
	while (Q--) {
		scanf("%d",&op);
		switch (op) {
			case 1: {
				scanf("%d", &x);
				to = x;
				rp++;
				break;
			}
			case 2: {
				scanf("%d%d", &i, &x);
				if (cnt[i] < rp) A[i] = to, cnt[i] = rp;
				A[i] += x;
				break;
			}
			case 3: {
				scanf("%d", &i);
				if (cnt[i] < rp) A[i] = to, cnt[i] = rp;
				printf("%lld\n", A[i]);
			}
		}
	}
	return 0;
}