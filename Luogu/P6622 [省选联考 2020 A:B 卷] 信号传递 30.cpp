#include <iostream>

const int maxN = 1e5;
const int maxM = 23;
const int inf = 1e9 + 10;

int n, m, k;
int s[maxN + 10];
int v[maxM + 10];
int p[maxM + 10];
int ans = inf;

void update() {
	int res = 0;
	for (int i = 1; i < n; i++) {
		int u = s[i];
		int v = s[i + 1];
		if (p[u] <= p[v]) {
			res += p[v] - p[u];
		} else {
			res += k * (p[u] + p[v]);
		}
	}
	ans = std::min(ans, res);
	return;
}

void DFS(int now) {
	if (now > m) {
		update();
		return;
	}
	for (int i = 1; i <= m; i++) {
		if (v[i]) continue;
		v[i] = true;
		p[i] = now;
		DFS(now + 1);
		v[i] = false;
	}
	return;
}

int main() {
	std::cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) std::cin >> s[i];
	DFS(1);
	std::cout << ans;
	return 0;
}