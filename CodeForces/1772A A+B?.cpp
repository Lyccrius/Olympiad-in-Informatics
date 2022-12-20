#include <cstdio>

int t;
int a, b;

void mian() {
	scanf("%1d+%1d", &a, &b);
	printf("%d\n", a + b);
	return;
}

int main() {
	scanf("%d", &t);
	while (t--) mian();
	return 0;
}