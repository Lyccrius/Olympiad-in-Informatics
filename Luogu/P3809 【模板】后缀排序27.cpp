#include <iostream>
#include <algorithm>
#include <cstring>

typedef char chr;

const int maxN = 1e6;

int n;
chr s[maxN + 10];
int sa[2 * maxN + 10];
int rk[2 * maxN + 10];
int bk[2 * maxN + 10];
int w;

int main() {
	std::cin >> (s + 1);
	n = strlen(s + 1);
	for (int i = 1; i <= n; i++) sa[i] = i, rk[i] = s[i];
	for (w = 1; w < n; w++) {
		std::sort(sa + 1, sa + n + 1, [](int x, int y) {
			if (rk[x] != rk[y]) return rk[x] < rk[y];
			return rk[x + w] < rk[y + w];
		});
		memcpy(bk, rk, sizeof(rk));
		for (int i = 1, j = 0; i <= n; i++) {
			if (bk[sa[i]] == bk[sa[i - 1]] && bk[sa[i] + w] == bk[sa[i - 1] + w]) rk[sa[i]] = j;
			else rk[sa[i]] = ++j;
		}
	}
	for (int i = 1; i <= n; i++) std::cout << sa[i] << ' ';
	return 0;
}