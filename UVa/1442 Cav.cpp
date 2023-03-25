#include <iostream>
#include <algorithm>

void promote() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	return;
}

const int maxN = 1e6;
const int inf = 1e9 + 10;

int t;
int n;
int p[maxN + 10];
int s[maxN + 10];
int l[maxN + 10];
int r[maxN + 10];
int ans;

void mian() {
	ans = 0;
	std::cin >> n;
	for (int i = 1; i <= n; i++) std::cin >> p[i];
	for (int i = 1; i <= n; i++) std::cin >> s[i];
	l[0] = inf;
	for (int i = 1; i <= n; i++) {
		l[i] = l[i - 1];
		l[i] = std::max(l[i], p[i]);
		l[i] = std::min(l[i], s[i]);
	}
	r[n + 1] = inf;
	for (int i = n; i >= 1; i--) {
		r[i] = r[i + 1];
		r[i] = std::max(r[i], p[i]);
		r[i] = std::min(r[i], s[i]);
	}
	for (int i = 1; i <= n; i++) {
		ans += std::min(l[i], r[i]) - p[i];
	}
	std::cout << ans << '\n';
	return;
}

int main() {
	promote();
	std::cin >> t;
	while (t--) mian();
	return 0;
}