#include <cstdio>

unsigned a;
unsigned b;

int main() {
	scanf("%u", &a);
	b += a % (1 << 16);
	b <<= 16;
	b += a / (1 << 16);
	printf("%u\n", b);
	return 0;
}