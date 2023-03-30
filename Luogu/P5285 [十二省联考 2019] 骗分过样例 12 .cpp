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
typedef char chr;
typedef __int128 i47;

const str _1_998244353 = "1_998244353";

str _subtask;

namespace subtask {
	namespace __1_998244353 {
		const int mod = 998244353;

		int t;
		lxl n;

		lxl read() {
			lxl ret = 0;
			lxl sym = 1;
			chr ch = getchar();
			while (!isdigit(ch)) {
				if (ch == '-') sym = - sym;
				ch = getchar();
			}
			while (isdigit(ch)) {
				ret = (ret * 10 + ch - '0') % (mod - 1);
				ch = getchar();
			}
			return (ret * sym % (mod - 1) + (mod - 1)) % (mod - 1);
		}

		lxl pow(lxl a, i47 b) {
			lxl ret = 1;
			while (b) {
				if (b & 1) ret = ret * a % mod;
				a = a * a % mod;
				b = b / 2;
			}
			return ret % mod;
		}

		void mian() {
			n = read();
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
	//promote();
	std::cin >> _subtask;
	if (_subtask == _1_998244353) subtask::__1_998244353::main();
}