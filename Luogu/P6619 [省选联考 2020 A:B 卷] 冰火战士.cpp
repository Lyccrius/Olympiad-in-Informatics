#include <iostream>
#include <algorithm>
#include <vector>

typedef long long lxl;
typedef std::vector<int> vic;

const int maxQ = 2e6;
const int logQ = 21;

int q;
int op[maxQ + 10];
int t[maxQ + 10], x[maxQ + 10], y[maxQ + 10];
int k[maxQ + 10];
vic raw;

struct BinaryIndexedTree {
	int n;
	lxl a[maxQ + 10];

	void init(int x) {
		n = x;
	}

	int lowbit(int x) {
		return x & (- x);
	}

	void add(int pos, int val) {
		while (pos <= n) {
			a[pos] += val;
			pos += lowbit(pos);
		}
		return;
	}

	lxl ask(int pos) {
		lxl ret = 0;
		while (pos) {
			ret += a[pos];
			pos -= lowbit(pos);
		}
		return ret;
	}

	lxl at(int pos) {
		return a[pos];
	}
} ice, fire;

lxl sum;

int main() {
	raw.push_back(0);
	std::cin >> q;
	for (int i = 1; i <= q; i++) {
		std::cin >> op[i];
		if (op[i] == 1) std::cin >> t[i] >> x[i] >> y[i], raw.push_back(x[i]);
		if (op[i] == 2) std::cin >> k[i];
	}
	std::sort(raw.begin(), raw.end());
	raw.erase(std::unique(raw.begin(), raw.end()), raw.end());
	for (int i = 1; i <= q; i++) if (op[i] == 1) x[i] = std::lower_bound(raw.begin(), raw.end(), x[i]) - raw.begin();
	ice.init(raw.size() - 1);
	fire.init(raw.size() - 1);
	for (int i = 1; i <= q; i++) {
		if (op[i] == 1) {
			if (t[i] == 0) ice.add(x[i], y[i]);
			if (t[i] == 1) fire.add(x[i] + 1, y[i]), sum += y[i];
		}
		if (op[i] == 2) {
			if (t[k[i]] == 0) ice.add(x[k[i]], - y[k[i]]);
			if (t[k[i]] == 1) fire.add(x[k[i]] + 1, - y[k[i]]), sum -= y[k[i]];
		}
		lxl sumice = 0, sumfire = sum;
		lxl res1 = 0, res2 = 0;
		int pos1 = 0, pos2 = 0;
		for (int p = logQ; p >= 0; p--) {
			int newpos = pos1 + (1 << p);
			int newsumice = sumice + ice.at(newpos);
			int newsumfire = sumfire - fire.at(newpos);
			if (newpos > raw.size() - 1) continue;
			if (newsumice < newsumfire) {
				pos1 = newpos;
				sumice = newsumice;
				sumfire = newsumfire;
			}
		}
		res1 = sumice;
		sumice = 0, sumfire = sum;
		if (pos1 < raw.size() - 1) {
			res2 = std::min(ice.ask(pos1 + 1), sum - fire.ask(pos1 + 1));
			for (int p = logQ; p >= 0; p--) {
				int newpos = pos2 + (1 << p);
				int newsumice = sumice + ice.at(newpos);
				int newsumfire = sumfire - fire.at(newpos);
				if (newpos > raw.size() - 1) continue;
				if (newsumice < newsumfire) {
					pos2 = newpos;
					sumice = newsumice, sumfire = newsumfire;
				} else if (std::min(newsumice, newsumfire) == res2) {
					pos2 = newpos;
					sumice = newsumice, sumfire = newsumfire;
				}
			}
		}
		if (std::max(res1, res2) == 0) std::cout << "Peace" << '\n';
		else if (res1 > res2) std::cout << raw[pos1] << ' ' << res1 * 2 << '\n';
		else std::cout << raw[pos2] << ' ' << res2 * 2 << '\n';
	}
	return 0;
}