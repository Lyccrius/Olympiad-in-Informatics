#include <cstdio>
#include <algorithm>

const int maxM = 1e5 + 10;

int m, n;
int bill[maxM];
int l, r;

struct ST {
	int f[maxM][30];
	int log[maxM];

	void PreWork() {
		for (int i = 2; i <= m; i++) log[i] = log[i >> 1] + 1;
		for (int i = 1; i <= m; i++) f[i][0] = bill[i];
		for (int j = 1; (1 << j) <= m; j++) for (int i = 1; i + (1 << j) - 1 <= m; i++) {
			f[i][j] = std::min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
		}
		return;
	}

	int Query(int l, int r) {
		int t = log[r - l + 1];
		return std::min(f[l][t], f[r - (1 << t) + 1][t]);
	}
} st;

int main() {
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= m; i++) scanf("%d", &bill[i]);
	st.PreWork();
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &l, &r);
		printf("%d ", st.Query(l, r));
	}
	return 0;
}