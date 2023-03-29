#include <iostream>
#include <algorithm>

const int maxN = 2500;
const int maxM = 3123750;
const int inf = 1e9 + 10;

int abs(int x) {
	if (x < 0) x = - x;
	return x;
}

int n, m, s;
int u, v;

namespace M0 {
	void mian() {
		for (int i = 1; i <= n; i++) std::cout << abs(i - s) << ' ';
		return;
	}
}

namespace M1 {
	void mian() {
		for (int i = 1; i <= n; i++) {
			int ans = inf;
			int uv = abs(u - v);
			int su = abs(u - s);
			int sv = abs(v - s);
			int ui = abs(u - i);
			int vi = abs(v - i);
			ans = std::min(ans, su + uv + vi);
			ans = std::min(ans, sv + uv + ui);
			ans = std::min(ans, su + uv + uv + ui);
			ans = std::min(ans, sv + uv + uv + vi);
			std::cout << ans << ' ';
		}
	}
}

int main() {
	std::cin >> n >> m >> s;
	for (int i = 1; i <= m; i++) std::cin >> u >> v;
	if (m == 0) M0::mian();
	if (m == 1) M1::mian();
	return 0;
}