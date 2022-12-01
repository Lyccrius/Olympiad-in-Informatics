#include <cstdio>
#include <algorithm>

const int maxN = 50000 + 10;

int N, K;
int diamonds[maxN];
int l, r;
int resL[maxN];
int resR[maxN];
int ans;

int main() {
    scanf("%d%d", &N, &K);
    l = 1;
    r = N;
    for (int i = 1; i <= N; i++) scanf("%d", &diamonds[i]);
    std::sort(diamonds + 1, diamonds + N + 1);
    for (int i = 1; i <= N; i++) {
		while (diamonds[i] - diamonds[l] > K && l <= i) l++;
		resL[i] = std::max(resL[i - 1], i - l + 1);
	}
	for (int i = N; i >= 1; i--) {
		while (diamonds[r] - diamonds[i] > K && r >= i) r--;
		resR[i] = std::max(resR[i + 1], r - i + 1);
	}
	for (int i = 1; i < N; i++) ans = std::max(ans, resL[i] + resR[i + 1]);
    printf("%d\n", ans);
    return 0;
}