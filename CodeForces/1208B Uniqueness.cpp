#include <cstdio>
#include <algorithm>
#include <set>

const int inf = 0x3f3f3f3f;
const int maxn = 2000 + 10;

int n;
int a[maxn];

std::set<int> cnt;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	int ans = inf;
	int l = 1;
	int r = n;
	while (r && !cnt.count(a[r])) cnt.insert(a[r--]);
	r++;
	while (l <= r && r <= n + 1) {
		while (!cnt.count(a[l])) cnt.insert(a[l++]);
		ans = std::min(ans, r - l);
        cnt.erase(a[r++]);
	}
	printf("%d\n", ans);
	return 0;
}