#include <iostream>
#include <vector>
#include <deque>

typedef std::vector<int> vic;
typedef std::deque<int> dic;

const int maxN = 1e3;
const int maxM = 2e5;

int n, m;
int x[maxM + 10], y[maxM + 10];
int f[maxN + 10][maxN + 10];
int g[maxN + 10][maxN + 10];
vic e[maxN + 10];
dic ans;

void floyd(int k) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == k) continue;
			if (j == k) continue;
			if (i == j) continue;
			f[i][j] += f[i][k] * f[k][j];
		}
	}
	return;
}

void dyolf(int k) {
	
}

int F(int u) {
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			g[i][j] = f[i][j];
		}
	}
	for (int v = 1; v <= u; v++) {
		if (g[u][v] && g[v][u]) {
			cnt++;
			
		}
	}
}

int h(int ban) {
	if (ban <= m) {
		f[x[ban]][y[ban]] = true;
		floyd(x[ban]);
		floyd(y[ban]);
	}
	int ret = 0;
	for (int u = 1; u <= n; u++) {
		ret += F(u);
	}
	return ret;
}

int main() {
	std::cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		std::cin >> x[i] >> y[i];
		e[x[i]].push_back(i);
	}
	for (int i = 1; i <= n; i++) f[i][i] = 1;
	for (int i = m + 1; i >= 1; i--) ans.push_front(h(i));
	return 0;
}