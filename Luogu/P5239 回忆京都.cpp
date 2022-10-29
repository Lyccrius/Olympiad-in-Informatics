#include <cstdio>

const int maxn = 1000 + 10;
const int mod = 19260817;

int q;
int n, m;

int table[maxn][maxn];

int main() {
	for (int i = 1; i <= 1000; i++) {
        for(int j = 1; j <= 1000; j++) {
		    table[i][j] = table[i - 1][j - 1]
                        + table[i - 1][j] + i;
            table[i][j] %= mod;
	    }
    }

	scanf("%d", &q);
	while (q--) {
		scanf("%d%d", &n, &m);
        printf("%d\n", table[m][n]);
	}

	return 0;
}