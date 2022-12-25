#include <cstdio>
#include <algorithm>
#include <map>

const int maxN = 1e6 + 10;

int T;
int n;
int a[maxN];
std::map<int, int> snow;
int last;
int ans;

void mian() {
	snow.clear();
	last = 0;
	ans = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		if (snow[a[i]] > last) last = snow[a[i]];
		snow[a[i]] = i;
		ans = std::max(ans, i - last);
	}
	printf("%d\n", ans);
	return;
}

int main() {
	scanf("%d", &T);
	while (T--) mian();
	return 0;
}