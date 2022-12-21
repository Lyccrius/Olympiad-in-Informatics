#include <cstdio>
#include <algorithm>

const int maxN = 5000 + 10;
const long long mod = 998244353;

int n;
long long A[maxN];
long long B[maxN];

struct Node {
	long long val;
	int bel;
	int cnt;

	bool operator<(Node other) const {
		if (val != other.val) return val > other.val;
		return bel < other.bel;
	}
} node[maxN << 1];

int cnt[2];

long long F[maxN << 1][maxN];

long long pow(long long a, long long b) {
	long long ret = 1;
	while (b) {
		if (b & 1) ret = ret * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ret;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", &A[i]), node[i].val = A[i], node[i].bel = 0;
	for (int i = 1; i <= n; i++) scanf("%lld", &B[i]), node[i + n].val = B[i], node[i + n].bel = 1;
	std::sort(node + 1, node + (n << 1) + 1);
	for (int i = 1; i <= (n << 1); i++) node[i].cnt = cnt[!node[i].bel], cnt[node[i].bel]++;
	for (int i = 0; i <= (n << 1); i++) F[i][0] = 1;
	for (int i = 1; i <= (n << 1); i++) for (int j = 1; j <= node[i].cnt; j++) F[i][j] = (F[i - 1][j - 1] * node[i].val % mod * (node[i].cnt - j + 1) % mod + F[i - 1][j]) % mod;
	long long tmp = 1;
	for (int i = 1; i <= n; i++) tmp = tmp * i % mod;
	long long res = pow(tmp, mod - 2) * F[n << 1][n] % mod;
	printf("%lld\n", res);
	return 0;
}