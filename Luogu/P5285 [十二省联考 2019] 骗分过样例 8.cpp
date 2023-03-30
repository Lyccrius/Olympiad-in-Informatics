#include <iostream>
#include <string>

void promote() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	return;
}

typedef std::string str;
typedef long long lxl;

const str _1_998244353 = "1_998244353";

str _subtask;

namespace subtask {
	namespace __1_998244353 {
		const int maxT = 1e5;
		const lxl maxN = 1e18;

		const int mod = 998244353;

		int t;
		lxl n;

		lxl pow(lxl a, lxl b) {
			lxl ret = 1;
			while (b) {
				if (b & 1) ret = ret * a % mod;
				a = a * a % mod;
				b = b / 2;
			}
			return ret % mod;
		}

		void mian() {
			std::cin >> n;
			std::cout << pow(19, n) << '\n';
			return;
		}

		void main() {
			std::cin >> t;
			while (t--) mian();
			return;
		}
	}
}

int main() {
	promote();
	std::cin >> _subtask;
	if (_subtask == _1_998244353) subtask::__1_998244353::main();
}