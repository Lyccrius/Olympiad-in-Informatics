#include <cstdio>
#include <algorithm>

const int maxn = 18 + 10;

int N;
int S[maxn];

int main() {
	int kase = 0;
	while (scanf("%d", &N) != EOF) {
		for (int i = 1; i <= N; i++) scanf("%d", &S[i]);
		long long ans = 0;
		for (int i = 1; i <= N; i++) for (int j = i; j <= N; j++) {
			long long mul = 1;
			for (int k = i; k <= j; k++) mul *= S[k];
			ans = std::max(ans, mul);
		}
		printf("Case #%d: The maximum product is %lld.\n\n",+ ++kase, ans);
	}
	return 0;
}