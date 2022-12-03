#include <cstdio>

const int maxN = 37336 + 10;

int n, R;
char str[maxN * 10];
int cnt;

int main() {
	scanf("%d%d", &n, &R);
	printf("%d=", n);
	while (n) {
		int a = n % R;
		n /= R;
		if (a < 0) a -= R, n--;
		if (a < 10) str[++cnt] = a + '0';
		else str[++cnt] = a - 10 + 'A';
	}
	for (int i = cnt; i >= 1; i--) printf("%c", str[i]);
	printf("(base%d)\n", R);
	return 0;
}