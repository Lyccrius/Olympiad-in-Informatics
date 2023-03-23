#include <iostream>

const int maxN = 5000;

int n;
int a[maxN + 10];
int l[maxN + 10][maxN + 10];
int g[maxN + 10][maxN + 10];
int sum;
int res;
int ans;
int cnt;

int main() {
	std::cin >> n;
	for (int i = 1; i <= n; i++) std::cin >> a[i];
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) l[i][j] = l[i - 1][j] + (a[i] < a[j]);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) g[i][j] = g[i - 1][j] + (a[i] > a[j]);
	for (int i = 1; i <= n; i++) sum += g[i][i]; ans = sum; cnt = 1;
	for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) {
		res = sum + (g[j][i] - g[i][i]) - (l[j][i] - l[i][i]) - (g[j][j] - g[i][j]) + (l[j][j] - l[i][j]);
		if (ans > res) {
			ans = res;
			cnt = 0;
		}
		if (ans == res) {
			cnt++;
		}
	}
	std::cout << ans << ' ' << cnt;
	return 0;
}