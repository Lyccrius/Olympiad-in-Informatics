#include <iostream>

void promote() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	return;
}

typedef long long lxl;

const int maxN = 5e4;
const int sqrN = 223;

int n;
int a[maxN + 10];
int b[maxN + 10];
int opt, l, r ,c;

class BlockArray {
	private:

		struct Array {
			int val;
			int bel;
		} array[maxN + 10];

		struct Block {
			int l, r;
			int tag;
			lxl sum;
		} block[sqrN + 10];

		void AddArray(int l, int r, int val) {
			for (int i = l; i <= r; i++) {
				array[i].val += val;
				block[array[i].bel].sum += val;
			}
			return;
		}

		void AddBlock(int l, int r, int val) {
			for (int i = l; i <= r; i++) {
				block[i].tag += val;
				block[i].sum += val * sqrN;
			}
			return;
		}

		int AskArray(int l, int r, int mod) {
			int ret = 0;
			for (int i = l; i <= r; i++) {
				ret = (1ll * ret + array[i].val + block[array[i].bel].tag) % mod;
			}
			return ret;
		}

		int AskBlock(int l, int r, int mod) {
			int ret = 0;
			for (int i = l; i <= r; i++) {
				ret = (1ll * ret + block[i].sum) % mod;
			}
			return ret;
		}

	public:

		void build() {
			for (int i = 1; i <= n; i++) array[i].val = a[i];
			for (int i = 1; i <= n; i++) array[i].bel = b[i];
			for (int i = 1; i <= n; i++) block[b[i]].r = i;
			for (int i = n; i >= 1; i--) block[b[i]].l = i;
			for (int i = 1; i <= n; i++) block[b[i]].sum += a[i];
			return;
		}

		void add(int l, int r, int val) {
			if (array[l].bel == array[r].bel) {
				AddArray(l, r, val);
				return;
			}
			AddArray(l, block[array[l].bel].r, val);
			AddArray(block[array[r].bel].l, r, val);
			AddBlock(array[l].bel + 1, array[r].bel - 1, val);
			return;
		}

		void ask(int l, int r, int mod) {
			mod = mod + 1;
			if (array[l].bel == array[r].bel) {
				std::cout << AskArray(l, r, mod) << '\n';
				return;
			}
			int ret = 0;
			ret = (1ll * ret + AskArray(l, block[array[l].bel].r, mod)) % mod;
			ret = (1ll * ret + AskArray(block[array[r].bel].l, r, mod)) % mod;
			ret = (1ll * ret + AskBlock(array[l].bel + 1, array[r].bel - 1, mod)) % mod;
			std::cout << ret << '\n';
		}
} BA;

int main() {
	std::cin >> n;
	for (int i = 1; i <= n; i++) std::cin >> a[i];
	for (int i = 1; i <= n; i++) b[i] = (i - 1) / sqrN + 1;
	BA.build();
	for (int i = 1; i <= n; i++) {
		std::cin >> opt >> l >> r >> c;
		if (opt == 0) {
			BA.add(l, r, c);
		} else if (opt == 1) {
			BA.ask(l, r, c);
		}
	}
	return 0;
}