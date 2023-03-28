#include <iostream>
#include <algorithm>

const int maxN = 2e5;

int n;
int a[maxN + 10];
int b[maxN + 10];
int ans;

int main() {
	std::cin >> n;
	for (int i = 1; i <= n; i++) std::cin >> a[i];
	std::sort(a + 1, a + n + 1);
	for (int k = n; k >= 1; k--) {
		if (a[k] - 1 <= ans) break;
		for (int i = 1; i <= n; i++) {
			b[i] = a[i] % a[k];
		}
		for (int i = 1; i <= n; i++) {
			if (i == k) continue;
			for (int j = 1; j <= n; j++) {
				if (j == k) continue;
				if (i == j) continue;
				ans = std::max(ans, (b[i] + b[j]) % a[k]);
			}
		}
	}
	std::cout << ans;
}