#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxN = 50 + 10;
const int inf = 1e9 + 10;

int n;
char str[maxN];
int f[maxN][maxN];

int main() {
	scanf("%s", str + 1);
	n = std::strlen(str + 1);
	std::memset(f, inf, sizeof(f));
	for (int i = 1; i <= n; i++) f[i][i] = 1;
	for (int len = 2; len <= n; len++) {
		for (int i = 1; i + len - 1 <= n; i++) {
			int j = i + len - 1;
			if (str[i] == str[j]) f[i][j] = std::min(f[i + 1][j], f[i][j - 1]);
			else for (int k = i; k < j; k++) f[i][j] = std::min(f[i][j], f[i][k] + f[k + 1][j]);
		}
	}
	printf("%d\n", f[1][n]);
	return 0;
}