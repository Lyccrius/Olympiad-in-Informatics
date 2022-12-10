#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXM=60;

const int maxN = 50 + 10;
const int inf = 1e9 + 10;

int n, c;
int a[maxN], b[maxN];
int f[maxN][maxN][2];
int pre[maxN];
int ans;

int main() {
  	scanf("%d%d", &n, &c);
  	std::memset(f, inf, sizeof(f));
	f[c][c][0] = 0;
	f[c][c][1] = 0;
  	for (int i = 1; i <= n; i++) scanf("%d%d", &a[i], &b[i]), pre[i] = pre[i - 1] + b[i];
  	for (int len = 2; len <= n; len++) for (int i = 1; i + len - 1 <= n; i++) {
    	int j = i + len - 1;
    	f[i][j][0] = std::min(f[i + 1][j][0] + (a[i + 1] - a[i]) * (pre[i] + pre[n] - pre[j]),
           					  f[i + 1][j][1] + (a[j] - a[i]) * (pre[i] + pre[n] - pre[j]));
    	f[i][j][1] = std::min(f[i][j - 1][0] + (a[j] - a[i]) * (pre[i - 1] + pre[n] - pre[j - 1]),
           					  f[i][j - 1][1] + (a[j] - a[j - 1]) * (pre[i - 1] + pre[n] - pre[j - 1]));
    }
  	ans = std::min(f[1][n][0], f[1][n][1]);
  	printf("%d\n", ans);
  	return 0;
}