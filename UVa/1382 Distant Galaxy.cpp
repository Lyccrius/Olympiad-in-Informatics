#include <cstdio>
#include <algorithm>

const int maxN = 100 + 10;

struct Planet {
	int x, y;
	bool operator<(const Planet &other) const {
		return x < other.x;
	}
};

int n;
Planet planets[maxN];
int y[maxN];
int left[maxN];
int on1[maxN];
int on2[maxN];

int solve() {
	std::sort(planets + 1, planets + n + 1);
	std::sort(y + 1, y + n + 1);
	int m = std::unique(y + 1, y + n + 1) - y;
	if (m <= 2) return n;
	int ans = 0;
	for (int a = 1; a <= m; a++) for (int b = a + 1; b <= m; b++) {
		int minY = y[a];
		int maxY = y[b];
		int cnt = 0;
		for (int i = 1; i <= n; i++) {
			if (i == 1 || planets[i].x != planets[i - 1].x) {
				cnt++;
				on1[cnt] = 0;
				on2[cnt] = 0;
				if (cnt) left[cnt] = left[cnt - 1] + on2[cnt - 1] - on1[cnt - 1];
				else left[cnt] = 0;
			}
			if (planets[i].y > minY && planets[i].y < maxY) on1[cnt]++;
			if (planets[i].y >= minY && planets[i].y <= maxY) on2[cnt]++;
		}
		if (cnt <= 2) return n;
		int in = 0;
		for (int i = 1; i <= cnt; i++) {
			ans = std::max(ans, left[i] + on2[i] + in);
			in = std::max(in, on1[i] - left[i]);
		}
	}
	return ans;
}

int main() {
	int kase = 0;
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 1; i <= n; i++) {
			scanf("%d%d", &planets[i].x, &planets[i].y);
			y[i] = planets[i].y;
		}
		printf("Case %d: %d\n", ++kase, solve());
	}
	return 0;
}