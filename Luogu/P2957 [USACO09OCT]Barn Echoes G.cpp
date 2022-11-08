#include <iostream>
#include <cstring>
#include <algorithm>

std::string a, b;

int main() {
	std::cin >> a >> b;

	for (int x = std::min(a.size(), b.size()) - 1; x >= 0; x --) {
		std::string prea = a.substr(0, x);
		std::string preb = b.substr(0, x);
		std::string sufa = a.substr(a.size() - x, x);
		std::string sufb = b.substr(b.size() - x, x);
		if (prea == sufb || preb == sufa) {
			std::cout << x << std::endl;
			return 0;
		}
	}

	return 0;
}