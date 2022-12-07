#include <cstdio>
#include <algorithm>

const int maxN = 1e5 + 10;
const int maxS = 600 + 10;

int n, w;
int sco[maxN];
int cnt[maxN];
int res[maxN];

int main() {
	scanf("%d%d", &n, &w);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &sco[i]);
		cnt[sco[i]]++;
		int p = std::max(1, i * w / 100);
		int sum = 0;
		for (int j = maxS; j >= 0 && sum < p; j--) {
			sum += cnt[j];
			if (sum >= p) {
				printf("%d ", j);
			}
		}
	}
	return 0;
}