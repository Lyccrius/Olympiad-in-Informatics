#include <cstdio>

int H, M;

bool check(int h, int m) {
	int hh = h / 10 * 10 + m / 10;
	int mm = h % 10 * 10 + m % 10;
	if (hh < 24 && mm < 60) return true;
	return false;
}

int main() {
	scanf("%d%d", &H, &M);
	while (!check(H, M)) {
		M = M / 10 * 10 + 10;
		if (M >= 60) M -= 60, H += 1;
		if (H >= 24) H -= 24;
	}
	printf("%d %d\n", H, M);
	return 0;
}