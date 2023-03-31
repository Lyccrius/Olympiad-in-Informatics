#include <iostream>
#include <vector>

typedef std::vector<int> vic;

const int maxN = 300;

int n;
int a[maxN + 10];
vic ans;

void mian() {
	for (int i = 1; i <= n; i++) std::cin >> a[i];
	for (int i = 1; i < n; i++) {
		for (int j = n; j >= 1; j--) {
			ans.push_back(2);
            if (j == n) continue;
			if (a[j] > a[j + 1]) {
				ans.push_back(1);
				std::swap(a[j], a[j + 1]);
			}
		}
	}
	while (!ans.empty()) std::cout << ans.back(), ans.pop_back();
	std::cout << '\n';
	return;
}

int main() {
	while (std::cin >> n && n) mian();
	return 0;
}