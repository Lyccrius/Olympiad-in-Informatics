#include <cstdio>
#include <algorithm>

const int maxN = 50000 + 10;

int N;
int ID[maxN];
int pre[maxN];
int fir[7];
int end[7];

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &ID[i]);
		pre[i] = pre[i - 1] + ID[i];
		pre[i] = pre[i] % 7;
		if (!fir[pre[i]] && pre[i]) fir[pre[i]] = i;
		end[pre[i]] = i;
	}
	int ans = 0;
	for (int i = 0; i < 7; i++) ans = std::max(ans, end[i] - fir[i]);
	printf("%d\n", ans);
	return 0;
}