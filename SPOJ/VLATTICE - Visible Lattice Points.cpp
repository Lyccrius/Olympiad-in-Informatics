#include <iostream>
#include <vector>

typedef long long lxl;
typedef std::vector<int> vic;

const int maxN = 1e6;

int t;
int n;
vic prime;
int vis[maxN + 10];
int mob[maxN + 10];

void sieve() {
	mob[1] = 1;
	for (int i = 2; i <= maxN; i++) {
		if (!vis[i]) {
			prime.push_back(i);
			mob[i] = -1;
		}
		for (auto j : prime) {
			if (i * j > maxN) break;
			vis[i * j] = true;
			mob[i * j] = - mob[i];
			if (i % j == 0) {
				mob[i * j] = 0;
				break;
			}
		}
	}
	return;
}

void mian() {
	lxl ans = 3;
	std::cin >> n;
	for (int i = 1; i <= n; i++) ans += 1ll * mob[i] * (n / i) * (n / i) * (n / i + 3);
	std::cout << ans << '\n';
	return;
}

int main() {
	sieve();
	std::cin >> t;
	while (t--) mian();
	return 0;
}