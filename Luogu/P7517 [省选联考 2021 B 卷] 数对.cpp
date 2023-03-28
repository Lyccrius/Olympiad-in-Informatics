#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

typedef long long lxl;
typedef std::vector<int> vic;
typedef std::map<int, int> mii;

const int maxN = 2e5;
const int maxA = 5e5;

int n;
int a[maxN + 10];
int c[maxA + 10];
int ans;

int main() {
	std::cin >> n;
	for (int i = 1; i <= n; i++) std::cin >> a[i];
	for (int i = 1; i <= n; i++) c[a[i]]++;
	for (int i = 1; i <= maxA; i++) {
		for (int j = 2; i * j <= maxA; j++) {
			ans += c[i] * c[i * j];
		}
		ans += c[i] * (c[i] - 1);
	}
	std::cout << ans;
	return 0;
}