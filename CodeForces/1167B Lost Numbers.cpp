#include <cstdio>
#include <algorithm>

int a[7] = {0, 4, 8, 15, 16, 23, 42};
int mul[5];

int main() {
	for (int i = 1; i <= 4; i++) {
		printf("? %d %d\n", i, i + 1);
		std::fflush(stdout);
		scanf("%d", &mul[i]);
	}
	do {
		bool _ = true;
		for (int i = 1; i <= 4; i++) {
			if (a[i] * a[i+1] != mul[i]) {
				_ = false;
				break;
			}
		}
		if (_) {
			printf("! ");
			for (int i = 1; i <= 6; i++) printf("%d ", a[i]);
			printf("\n");
			break;
		}
	} while (std::next_permutation(a + 1, a + 6 + 1));
	return 0;
}