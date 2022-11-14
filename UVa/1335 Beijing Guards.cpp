#include <cstdio>
#include <algorithm>

const int maxn = 1e6 + 10;

int n;
int r[maxn];

int left[maxn];
int right[maxn];

bool check(int p) {
	int x = r[1];
	int y = p - r[1];
	left[1] = x;
	right[1] = 0;
	for (int i = 2; i <= n; i++) {
		if (i % 2) {
			right[i] = std::min(y - right[i - 1], r[i]);
			left[i] = r[i] - right[i];
		} else {
			left[i] = std::min(x - left[i - 1], r[i]);
			right[i] = r[i] - left[i];
		}
	}
	return left[n] == 0;
}

int main() {
	while (scanf("%d", &n) && n) {
		for (int i = 1; i <= n; i++) scanf("%d", &r[i]);
		r[n + 1] = r[1];
		int L = 0;
		int R = 0;
		for (int i = 1; i <= n; i++) L = std::max(L, r[i] + r[i + 1]);
		if (n % 2) {
			for (int i = 1; i <= n; i++) R = std::max(R, r[i] * 3);
			while (L < R) {
				int M = (L + R) / 2;
				if (check(M)) R = M;
				else L = M + 1;
			}
		}
		printf("%d\n", L);
	}
	return 0;
}