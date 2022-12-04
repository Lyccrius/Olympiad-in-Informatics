#include <cstdio>
#include <algorithm>
#include <vector>

const int maxN = 100 + 10;
const int maxM = 2000 + 10;

int n;
struct Portal {
	int t, d, c, id;

	bool operator<(Portal other) const {
		return d < other.d;
	}
} portal[maxN];
int m;
int f[maxM];
std::vector<int> order[maxM];
int ans;
int pos;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d%d", &portal[i].t, &portal[i].d, &portal[i].c);
		portal[i].id = i;
		m = std::max(m, portal[i].d);
	}
	std::sort(portal + 1, portal + n + 1);
	for (int i = 1; i <= n; i++) {
		for (int j = portal[i].d - 1; j >= portal[i].t; j--) if (f[j - portal[i].t] + portal[i].c > f[j]) {
			f[j] = f[j - portal[i].t] + portal[i].c;
			order[j] = order[j - portal[i].t];
			order[j].push_back(portal[i].id);
		}
	}
	for (int i = 1; i <= m; i++) if (f[i] > ans) {
		ans = f[i];
		pos = i;
	}
	printf("%d\n", ans);
	printf("%d\n", order[pos].size());
	for (auto i : order[pos]) printf("%d ", i);
	return 0;
}