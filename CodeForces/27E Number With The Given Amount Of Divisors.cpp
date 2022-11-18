#include <cstdio>
#include <algorithm>

const long long inf = 1e18 + 10;

int n;
long long ans = inf;
int prime[31] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53}; 

void DFS(long long cur, int k, long long cnt) {
	if (cur > ans || cur < 1 || k > 16 || cnt > n) return;
	if (cnt == n) {
		ans = std::min(ans, cur);
	}
	DFS(cur, k + 1, cnt);
	for (int i = 1; i <= 63; i++) {
		cur *= prime[k];
		if (cur > ans || cur < 1) break;
		if (n % (i + 1) == 0) DFS(cur, k + 1, cnt * (i + 1));
	}
	return;
}

int main() {
	scanf("%d", &n);
	DFS(1, 1, 1);
	printf("%lld\n", ans);
	return 0;
}