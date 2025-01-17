#include <iostream>
#include <complex>
#include <cmath>

typedef double dbl;
typedef std::complex<dbl> cmd;

const int maxN = 500;
const int maxA = 500000;
const int logA = 20;
const int maxM = 1 << logA;
const dbl pi = acos(-1.0);

int n;
int alo, ahi;
int c[maxM + 10];
cmd f[maxM + 10];

void FFT(cmd *a, int n, int k) {
	if (n == 1) return;
	int mid = n / 2;
	cmd al[mid];
	cmd ar[mid];
	for (int i = 0; i < mid; i++) {
		al[i] = a[2 * i];
		ar[i] = a[2 * i + 1];
	}
	FFT(al, mid, k);
	FFT(ar, mid, k);
	cmd w1(cos(2.0 * pi / n), k * sin(2.0 * pi / n));
	cmd wk(1.0, 0.0);
	for (int i = 0; i < mid; i++, wk *= w1) {
		a[i] = al[i] + wk * ar[i];
		a[i + mid] = al[i] - wk * ar[i];
	}
	return;
}

struct SegmentTree {
	struct Node {
		int pos;
		int val;
	} node[4 * maxM + 10];

	Node Merge(Node a, Node b) {
		if (a.val >= b.val) return a;
		return b;
	}

	void PushUp(int u) {
		node[u] = Merge(node[2 * u], node[2 * u + 1]);
		return;
	}

	void Modify(int u, int l, int r, int pos, int val) {
		if (l == r) {
			node[u].pos = l;
			node[u].val = val;
			return;
		}
		int mid = (l + r) / 2;
		if (pos <= mid) Modify(2 * u, l, mid, pos, val);
		if (pos >= mid + 1) Modify(2 * u + 1, mid + 1, r, pos, val);
		PushUp(u);
		return;
	}

	Node Query(int u, int l, int r, int s, int t) {
		if (s <= l && r <= t) return node[u];
		int mid = (l + r) / 2;
		if (t <= mid) return Query(2 * u, l, mid, s, t);
		if (s >= mid + 1) return Query(2 * u + 1, mid + 1, r, s, t);
		return Merge(Query(2 * u, l, mid, s, t), Query(2 * u + 1, mid + 1, r, s, t));
	}
} SGT;

int main() {
	for (int i = 1; i <= maxA; i++) for (int j = i; j <= maxA; j += i) c[j]++;
    for (int i = 1; i <= maxA; i++) f[i].real(c[i]);
	FFT(f, maxM, 1);
	for (int i = 0; i < maxM; i++) f[i] = f[i] * f[i];
	FFT(f, maxM, -1);
	for (int i = 1; i < maxM; i++) SGT.Modify(1, 1, maxM, i, (int) (f[i].real() / maxM + 0.5));
	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> alo >> ahi;
		SegmentTree::Node ans = SGT.Query(1, 1, maxM, alo, ahi);
		std::cout << ans.pos << ' ' << ans.val << '\n';
	}
	return 0;
}