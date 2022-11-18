#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

const int inf = 1e9 + 10;
const long long Inf = 1e18 + 10;
const int maxN = 2e5 + 10;

int n, m;
long long s;

struct Mineral {
	int w;
	int v;
} mineral[maxN];
struct Range {
	int l;
	int r;
} range[maxN];

int maxW = 0;
int minW = inf;

long long check(int w) {
	long long res = 0;
	long long cntW[maxN];
	long long sumV[maxN];
	memset(cntW , 0 , sizeof(cntW));
	memset(sumV , 0 , sizeof(sumV));
	for (int i = 1; i <= n; i++) {
		if (mineral[i].w >= w) {
			cntW[i] = cntW[i - 1] + 1;
			sumV[i] = sumV[i - 1] + mineral[i].v;
		} else {
			cntW[i] = cntW[i - 1];
			sumV[i] = sumV[i - 1]; 
		}
	}
	for (int i = 1; i <= m; i++) res += (cntW[range[i].r] - cntW[range[i].l - 1]) * (sumV[range[i].r] - sumV[range[i].l - 1]);
	return res;
}
int main() {
	scanf("%d%d%lld", &n, &m, &s);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &mineral[i].w, &mineral[i].v);
		maxW = std::max(maxW, mineral[i].w);
		minW = std::min(minW, mineral[i].w);
	}
	for (int i = 1; i <= m; i++) scanf("%d%d", &range[i].l, &range[i].r);
	int l = minW - 1;
	int r = maxW + 2;
	long long ans = Inf;
	while (l <= r) {
		int mid = (l + r) / 2;
		long long res = check(mid);
		if (res >= s) l = mid + 1;
		else r = mid - 1;
		ans = std::min(ans, std::abs(res - s));
	}
	printf("%lld\n", ans);
	return 0;
}