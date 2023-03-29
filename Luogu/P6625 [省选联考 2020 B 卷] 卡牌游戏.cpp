#include <iostream>
#include <algorithm>
#include <queue>

typedef long long lxl;
typedef std::priority_queue<int> pri;

const int maxN = 1e5;

int n;
lxl a[maxN + 10];
lxl sum;
lxl ans;

int main() {
	std::cin >> n;
	for (int i = 1; i <= n; i++) std::cin >> a[i];
	for (int i = 1; i <= n; i++) {
		sum += a[i];
		if (sum > 0 && i > 1) ans += sum;
	}
	std::cout << ans << '\n';
	return 0;
}