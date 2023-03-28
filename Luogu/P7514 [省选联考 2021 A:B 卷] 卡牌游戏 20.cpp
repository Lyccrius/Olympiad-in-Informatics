#include <iostream>
#include <algorithm>

const int maxN = 1e6;
const int inf = 1e9;

int n, m;
int a[maxN + 10];
int b[maxN + 10];
int ans = inf;

void DFS(int now, int cnt, int max, int min) {
	if (cnt > m) return;
	if ((n - now + 1) < (m - cnt)) return;
	if (max - min > ans) return;
	if (now > n) {
		ans = std::min(ans, max - min);
		return;
	}
	//printf("DFS %d, %d, %d, %d\n", now, cnt, max, min);
	DFS(now + 1, cnt, std::max(max, a[now]), std::min(min, a[now]));
	DFS(now + 1, cnt + 1, std::max(max, b[now]), std::min(min, b[now]));
	return;
}

int main() {
	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) std::cin >> a[i];
	for (int i = 1; i <= n; i++) std::cin >> b[i];
	DFS(1, 0, 0, inf);
	std::cout << ans << '\n';
	return 0;
}