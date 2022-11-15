#include <cstdio>
#include <cstring>

const int maxn = 2e6 + 10;
const int maxx = 100 + 10;

int n;
int x;
int ages[maxx];

int main() {
	while (scanf("%d", &n) == 1 && n) {
		std::memset(ages, 0, sizeof(ages));
		for (int i = 1; i <= n; i++) {
			scanf("%d", &x);
			ages[x]++;
		}
		bool first = true;
		for (int i = 1; i <= 100; i++) {
			for (int j = 1; j <= ages[i]; j++) {
				if (!first) printf(" ");
				first = false;
				printf("%d", i);
			}
		}
		printf("\n");
	}
	return 0;
}