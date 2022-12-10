#include <cstdio>
#include <algorithm>

const int maxN = 20000 + 10;

int N, B;
int H[maxN];
long long S = 0;

int main() {
	scanf("%d%d", &N, &B);
	for (int i = 1; i <= N; i++) scanf("%d", &H[i]);
	std::sort(H + 1, H + N + 1);
	for (int i = N; i >= 1; i--) {
		S += H[i];
		if (S >= B) {
			printf("%d\n", N - i + 1);
			return 0;
		}
	}
	return 0;
}