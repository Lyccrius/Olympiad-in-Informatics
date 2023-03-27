#include <iostream>

void promote() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	return;
}

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
		} block[sqrN + 10];

		void Add(int l, int r, int val) {
			if (b[l] == b[r]) {
				for (int i = l; i <= r; i++) array[i].val += val;
				return;
			}
			for (int i = l; i <= block[b[l]].r; i++) array[i].val += val;
			for (int i = block[b[r]].l; i <= r; i++) array[i].val += val;
			for (int i = b[l] + 1; i <= b[r] - 1; i++) block[i].tag += val;
			return;
		}

		int Ask(int pos) {
			return array[pos].val + block[b[pos]].tag;
		}

	public:

		void build() {
			for (int i = 1; i <= n; i++) array[i].val = a[i];
			for (int i = 1; i <= n; i++) array[i].bel = b[i];
			for (int i = 1; i <= n; i++) block[b[i]].r = i;
			for (int i = n; i >= 1; i--) block[b[i]].l = i;
			return;
		}

		void add(int l, int r, int c) {
			Add(l, r, c);
			return;
		}

		void ask(int r) {
			std::cout << Ask(r) << '\n';
			return;
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
			BA.ask(r);
		}
	}
	return 0;
}