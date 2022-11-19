#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

const int inf = 1e9 + 10;
const int maxN = 1.5e5 + 10;
const int maxY = 3e6 + 10;

int N;
int x, y;
std::vector<int> range[maxY];

int main() {
	scanf("%d", &N);
	int l = inf;
	int r = 0;
	for (int i = 1; i <= N; i++) {
		scanf("%d%d", &x, &y);
		range[y].push_back(x);
		l = std::min(l, y);
		r = std::max(r, y);
	}
	int f[maxY];
	std::memset(f, 0, sizeof(f));
	for (int j = l; j <= r; j++) {
		f[j] = f[j - 1];
		while (!range[j].empty()) {
			int i = range[j].back();
			range[j].pop_back();
			f[j] = std::max(f[j], f[i - 1] + j - i + 1);
		}
	}
	printf("%d\n", f[r]);
	return 0;
}