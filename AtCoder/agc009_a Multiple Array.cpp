#include <iostream>

typedef long long lxl;

const int maxN = 1e5;

int N;
lxl A[maxN + 10];
lxl B[maxN + 10];
lxl ans;

int main() {
	std::cin >> N;
	for (int i = 1; i <= N; i++) {
		std::cin >> A[i];
		std::cin >> B[i];
	}
	for (int i = N; i >= 1; i--) {
		A[i] += ans;
		if (A[i] % B[i] == 0) continue;
		ans += (A[i] / B[i] + 1) * B[i] - A[i];
	}
	std::cout << ans << '\n';
	return 0;
}