#include <iostream>
#include <algorithm>

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
int opt, l, r, c;

class BlockArray {
	private:

		struct Array {
			int val;
			int pos;
			int bel;
		} array[maxN + 10];

		struct Block {
			int l, r;
			int tag;
		} block[sqrN + 10];

		static bool cmpByPos(const Array &x, const Array &y) {
			return x.pos < y.pos;
		}

		static bool cmpByVal(const Array &x, const Array &y) {
			return x.val < y.val;
		}

		void Build() {
			for (int i = 1; i <= n; i++) array[i].pos = i;
			for (int i = 1; i <= n; i++) array[i].val = a[i];
			for (int i = 1; i <= n; i++) array[i].bel = b[i];
			for (int i = 1; i <= n; i++) block[b[i]].r = i;
			for (int i = n; i >= 1; i--) block[b[i]].l = i;
			for (int i = 1; i <= b[n]; i++) std::sort(array + block[i].l, array + block[i].r + 1, cmpByVal);
			return;
		}

		void AddArray(int l, int r, int val) {
			std::sort(array + block[array[l].bel].l, array + block[array[r].bel].r + 1, cmpByPos);
			for (int i = l; i <= r; i++) array[i].val += val;
			std::sort(array + block[array[l].bel].l, array + block[array[r].bel].r + 1, cmpByVal);
			return;
		}

		void AddBlock(int l, int r, int val) {
			for (int i = array[l].bel + 1; i <= array[r].bel - 1; i++) block[i].tag += val;
			return;
		}

		int AskArray(int l, int r, int val) {
			int ret = 0;
			//std::sort(array + block[array[l].bel].l, array + block[array[r].bel].r + 1, cmpByPos);
			//for (int i = l; i <= r; i++) if (array[i].val < val - block[array[i].bel].tag) ret++;
			//std::sort(array + block[array[l].bel].l, array + block[array[r].bel].r + 1, cmpByVal);
			for (int i = block[array[l].bel].l; i <= block[array[r].bel].r; i++) if (l <= array[i].pos && array[i].pos <= r) if (array[i].val < val - block[array[i].bel].tag) ret++;
			return ret;
		}

		int AskBlock(int l, int r, int val) {
			int ret = 0;
			for (int i = array[l].bel + 1; i <= array[r].bel - 1; i++) ret += std::lower_bound(array + block[i].l, array + block[i].r + 1, (Array) {val - block[i].tag}, cmpByVal) - (array + block[i].l);
			return ret;
		}

	public:

		void build() {
			Build();
			return;
		}

		void add(int l, int r, int val) {
			if (array[l].bel == array[r].bel) {
				AddArray(l, r, val);
				return;
			}
			AddArray(l, block[array[l].bel].r, val);
			AddArray(block[array[r].bel].l, r, val);
			AddBlock(l, r, val);
			return;
		}

		int ask(int l, int r, int val) {
			int ret = 0;
			if (array[l].bel == array[r].bel) {
				return AskArray(l, r, val * val);
			}
			ret += AskArray(l, block[array[l].bel].r, val * val);
			ret += AskArray(block[array[r].bel].l, r, val * val);
			ret += AskBlock(l, r, val * val);
			return ret;
		}
} BA;

int main() {
	promote();
	std::cin >> n;
	for (int i = 1; i <= n; i++) std::cin >> a[i];
	for (int i = 1; i <= n; i++) b[i] = (i - 1) / sqrN + 1;
	BA.build();
	for (int i = 1; i <= n; i++) {
		std::cin >> opt >> l >> r >> c;
		if (opt == 0) {
			BA.add(l, r, c);
		} else if (opt == 1) {
			std::cout << BA.ask(l, r, c) << '\n';
		}
	}
	return 0;
}