#include <cstdio>
#include <algorithm>

const int maxN = 50000 + 10;

int n, q;
int h[maxN];
int a, b;
int log[maxN];
int f1[maxN][20];
int f2[maxN][20];

void PreWork() {
    for (int i = 2; i <= n; i++) log[i] = log[i >> 1] + 1;
    for (int i = 1; i <= n; i++) f1[i][0] = h[i];
    for (int i = 1; i <= n; i++) f2[i][0] = h[i];
	for (int j = 1; j <= 20; j++) for (int i = 1; i + (1 << j) - 1 <= n; i++) {
			f1[i][j] = std::max(f1[i][j - 1], f1[i + (1 << (j - 1))][j - 1]);
            f2[i][j] = std::min(f2[i][j - 1], f2[i + (1 << (j - 1))][j - 1]);
    }
    return;
}

int Query(int x, int y) {
    int t = log[y - x + 1];
    int mx = std::max(f1[x][t], f1[y - (1 << t) + 1][t]);
    int mn = std::min(f2[x][t], f2[y - (1 << t) + 1][t]);
    return mx - mn;
}

int main() {
    scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; ++i) scanf("%d", &h[i]);
    PreWork();
	while (q--) {
        scanf("%d%d", &a, &b);
        printf("%d\n", Query(a, b));
    }
	return 0;
}