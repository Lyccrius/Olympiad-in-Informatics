#include <cstdio>
#include <algorithm>

const int maxN = 2e5 + 10;

int t;
int n;
int s[maxN];

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		int maxS = 0;
		int locS;
		int secS;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &s[i]);
			if (maxS <= s[i]) {
				secS = maxS;
				maxS = s[i];
				locS = i;
			} else if (secS <= s[i]) secS = s[i];
		}
		for (int i = 1; i <= n; i++) {
			if (i != locS) printf("%d ", s[i] - maxS);
			else printf("%d ", s[i] - secS);
		}
		printf("\n");
	}
	return 0;
}