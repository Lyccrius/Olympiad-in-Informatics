#include <iostream>
#include <algorithm>

const int maxN = 100;

int t;
int n;
int a[maxN + 10];
int b[maxN + 10];

void mian() {
	std::cin >> n;
	for (int i = 1; i <= n; i++) std::cin >> a[i];
	for (int i = 1; i <= n; i++) std::cin >> b[i];
	for (int i = 1; i <= n; i++) if (a[i] > b[i]) std::swap(a[i], b[i]);
	for (int i = 1; i <= n; i++) if (a[i] > a[n]) {std::cout << "No" << '\n'; return;}
	for (int i = 1; i <= n; i++) if (b[i] > b[n]) {std::cout << "No" << '\n'; return;};
	std::cout << "Yes" << '\n';
	return;
}

int main() {
	std::cin >> t;
	while (t--) mian();
	return 0;
}