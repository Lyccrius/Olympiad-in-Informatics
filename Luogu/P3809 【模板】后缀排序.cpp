#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn = 1e6 + 10;
const int mod = 131;

int n;
char s[maxn];

struct SuffixArray {
	struct Hash {
		unsigned long long hash[maxn];
		unsigned long long pow[maxn];

		unsigned long long Query(int l, int r) {
			return hash[r] - hash[l - 1] * pow[r - l + 1];
		}
	};

	Hash hash;
	int rk[maxn];
	int sa[maxn];

	void Init() {
		hash.pow[0] = 1;
		for (int i = 1; i <= n; i++) {
			hash.hash[i] = hash.hash[i - 1] * mod + (s[i] - '0' + 1);
			hash.pow[i] = hash.pow[i - 1] * mod;
			sa[i] = i;
		}
		return;
	}

	int LCP(int x, int y) {
		int l = 0, r = std::min(n - x + 1, n - y + 1);
		while (l < r) {
			int mid = (l + r + 1) >> 1;
			if (hash.Query(x, x + mid - 1) == hash.Query(y, y + mid - 1)) l = mid;
			else r = mid - 1;
		}
		return l;
	}

	void calc() {
		for (int i = 1; i <= n; i++) rk[sa[i]] = i;
		return;
	}
};

SuffixArray suffixArray;

bool cmp(int x, int y) {
	int len = suffixArray.LCP(x, y);
	return s[x + len] < s[y + len];
}

int main() {
	scanf("%s", s + 1);
	n = std::strlen(s + 1);
	suffixArray.Init();
	std::stable_sort(suffixArray.sa + 1, suffixArray.sa + n + 1, cmp);
	for (int i = 1; i <= n; i++) printf("%d ", suffixArray.sa[i]);
	return 0;
}