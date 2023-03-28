#include <iostream>
#include <cmath>

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

		void SqrArray(int l, int r) {
			for (int i = l; i <= r; i++) {
				block[array[i].bel].sum -= array[i].val;
				array[i].val = std::sqrt(array[i].val);
				block[array[i].bel].sum += array[i].val;
			}
			return;
		}

		bool Check(int x) {
			for (int i = block[x].l; i <= block[x].r; i++) {
				if (array[i].val > 1) return false;
			}
			return true;
		}

		void MakeTag(int x) {
			block[x].tag = true;
			return;
		}

		void SqrBlock(int l, int r) {
			for (int i = l; i <= r; i++) {
				if (block[i].tag) continue;
				SqrArray(block[i].l, block[i].r);
				if (Check(i)) MakeTag(i);
			}
			return;
		}

		int AskArray(int l, int r) {
			int ret = 0;
			for (int i = l; i <= r; i++) {
				ret += array[i].val;
			}
			return ret;
		}

		int AskBlock(int l, int r) {
			int ret = 0;
			for (int i = l; i <= r; i++) {
				ret += block[i].sum;
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

		void sqr(int l, int r) {
			if (array[l].bel == array[r].bel) {
				SqrArray(l, r);
				return;
			}
			SqrArray(l, block[array[l].bel].r);
			SqrArray(block[array[r].bel].l, r);
			SqrBlock(array[l].bel + 1, array[r].bel - 1);
			return;
		}

		void ask(int l, int r) {
			if (array[l].bel == array[r].bel) {
				std::cout << AskArray(l, r) << '\n';
				return;
			}
			int ret = 0;
			ret += AskArray(l, block[array[l].bel].r);
			ret += AskArray(block[array[r].bel].l, r);
			ret += AskBlock(array[l].bel + 1, array[r].bel - 1);
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
			BA.sqr(l, r);
		} else if (opt == 1) {
			BA.ask(l, r);
		}
	}
	return 0;
}