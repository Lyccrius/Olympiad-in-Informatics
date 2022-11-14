#include <cstdio>
#include <cstring>

const int maxn = 10 + 10;

int T;
int n;
char grid[maxn][maxn];

int main() {
	scanf("%d", &T);
	for (int kase = 1; kase <= T; kase++) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) scanf(" %c", &grid[i][j]);
		for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) if (grid[i][j] == '.') {
			for (char ch = 'A'; ch <= 'Z'; ch++) {
				bool flag = true;
				if (i != 1 && grid[i - 1][j] == ch) flag = false;
				if (i != n && grid[i + 1][j] == ch) flag = false;
				if (j != 1 && grid[i][j - 1] == ch) flag = false;
				if (j != n && grid[i][j + 1] == ch) flag = false;
				if (flag) {
					grid[i][j] = ch;
					break;
				}
			}
		}
		printf("Case %d:\n", kase);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) printf("%c", grid[i][j]);
			printf("\n");
		}
	}
	return 0;
}