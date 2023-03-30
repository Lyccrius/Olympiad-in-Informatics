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
const str _2p = "2p";

str _subtask;

namespace subtask {
	namespace __1_998244353 {
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
	
	namespace __2p {
		const int maxN = 1e6;

		int t;
		int l, r;
		int vis[maxN + 10];

		void init() {
			for (int i = 2; i <= maxN; i++) {
				if (vis[i]) continue;
				for (int j = 2 * i; j <= maxN; j += i) {
					vis[j] = true;
				}
			}
			return;
		}

		void mian() {
			std::cin >> l >> r;
			for (int i = l; i <= r; i++) {
				if (vis[i]) {
					std::cout << '.';
				} else {
					std::cout << 'p';
				}
			}
			std::cout << '\n';
			return;
		}

		void main() {
			init();
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
	if (_subtask == _2p) subtask::__2p::main();
	return 0;
}