#include <cstdio>

const int maxN = 10 + 1;

int n;
int map[1 << maxN][1 << maxN];

int main() {
	scanf("%d", &n);
	map[0][(1 << n) + 1] = 1;
	for (int i = 1; i <= (1 << n); i++) {
		for (int j = 1; j <= (1 << n); j++) {
			map[i][j] = map[i - 1][j] ^ map[i - 1][j + 1];
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	return 0;
}