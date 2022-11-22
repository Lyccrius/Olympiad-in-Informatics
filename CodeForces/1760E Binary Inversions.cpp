#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

const int maxN = 2e5 + 10;

int t;
int n;
int a[maxN];
int cnt[maxN];

int main() {
	scanf("%d", &t);
	while (t--) {
        std::memset(a, 0, sizeof(a));
        std::memset(cnt, 0, sizeof(cnt));
		scanf("%d", &n);
		std::queue<int> one;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			cnt[i] = cnt[i - 1];
			if (a[i]) {
				one.push(i);
				cnt[i]++;
			}
		}
		long long ans = 0;
		while (!one.empty()) {
			int x = one.front();
			one.pop();
			ans += n - x - one.size();
		}
		int l;
		int r;
		for (l = 1; l <= n; l++) {
            if (a[l] == 0) {
                break;
            }
        }
		for (r = n; r >= 1; r--) {
            if (a[r] == 1) {
                break;
            }
        }
		long long res1 = 0;
        long long res2 = 0;
        if (l <= n) res1 = n - l - cnt[n];
		if (r >= 1) res2 = r - n + cnt[n] - 1;
		long long res = std::max(res1, res2);
		res = std::max((long long)0, res);
		printf("%lld\n", ans + res);
	}
	return 0;
}