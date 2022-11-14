#include <cstdio>
#include <cstring>
#include <queue>

const int maxn = 200 + 10;

int N, A, B;
int K[maxn];

int res[maxn];

int BFS() {
	std::memset(res, -1, sizeof(res));
	std::queue<int> q;
	q.push(A);
	res[A] = 0;
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		if (x == B) return res[x];
		if (x - K[x] >= 0 && x - K[x] < maxn && res[x - K[x]] == -1) {
			res[x - K[x]] = res[x] + 1;
			q.push(x - K[x]);
		}
		if (x + K[x] >= 0 && x + K[x] < maxn && res[x + K[x]] == -1) {
			res[x + K[x]] = res[x] + 1;
			q.push(x + K[x]);
		}
	}
	return -1;
}

int main() {
	scanf("%d%d%d", &N, &A, &B);
	for (int i = 1; i <= N; i++) scanf("%d", &K[i]);
	printf("%d\n", BFS());
	return 0;
}