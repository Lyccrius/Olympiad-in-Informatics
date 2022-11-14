#include <cstdio>
#include <cstring>
#include <queue>

const int maxn = 1e4 + 10;

int n, m;

int res[maxn];

int BFS() {
	std::memset(res, -1, sizeof(res));
	std::queue<int> q;
	q.push(n);
	res[n] = 0;
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		if (x == m) return res[x];
		if (x - 1 >= 0 && x - 1 < maxn && res[x - 1] == -1) {
			res[x - 1] = res[x] + 1;
			q.push(x - 1);
		}
		if (x * 2 >= 0 && x * 2 < maxn && res[x * 2] == -1) {
			res[x * 2] = res[x] + 1;
			q.push(x * 2);
		}
	}
	return -1;
}

int main() {
	scanf("%d%d", &n, &m);
	printf("%d\n", BFS());
	return 0;
}