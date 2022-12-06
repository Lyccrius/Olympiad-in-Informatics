#include <cstdio>
#include <algorithm>

const int maxM = 2e5 + 10;

long long M, D;
long long L, n;
long long t;

struct ST {
	int log[maxM];
	int table[maxM][30];
	int head;

	void Init() {
		for (int i = 2; i <= M; i++) log[i] = log[i >> 1] + 1;
		return;
	}

	int Query(long long pos) {
		int l = head - pos + 1;
		int r = head;
		int p = log[r - l + 1];
		return std::max(table[r][p], table[l + (1 << p) - 1][p]);
	}

	void Add(long long val) {
		head++;
		table[head][0] = val;
		for (int i = 1; head - (1 << i) >= 0; i++) table[head][i] = std::max(table[head][i - 1], table[head - (1 << (i - 1))][i - 1]);
		return;
	}
} st;

int main() {
	scanf("%lld%lld", &M, &D);
	st.Init();
	while (M--) {
		char ch;
		scanf(" %c", &ch);
		if (ch == 'Q') {
			scanf("%lld", &L);
			t = st.Query(L);
			printf("%lld\n", t);
		} else {
			scanf("%lld", &n);
			st.Add((n + t) % D);
		}
	}
	return 0;
}