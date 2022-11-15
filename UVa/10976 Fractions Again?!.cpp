#include <cstdio>

const int maxk = 10000 + 10;

int k;

int main() {
	while (scanf("%d", &k) && k) {
		int ans = 0;
        int ansX[maxk];
		int ansY[maxk];
		for (int y = k + 1; y <= (k << 1); y++) {
			if ((y * k) % (y - k)) continue;
            ans++;
            ansX[ans] = (y * k) / (y - k);
			ansY[ans] = y;
		}
		printf("%d\n", ans);
		for (int i = 1; i <= ans; i++) printf("1/%d = 1/%d + 1/%d\n", k, ansX[i], ansY[i]);
	}
	return 0;
}