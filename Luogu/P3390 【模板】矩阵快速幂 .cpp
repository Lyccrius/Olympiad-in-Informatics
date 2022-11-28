#include <cstdio>
#include <cstring>

const int maxN = 100 + 10;
const int mod = 1e9 + 7;

long long n, k;

struct Matrix {
	long long a[maxN][maxN];

	Matrix() {
		std::memset(a, 0, sizeof(a));
		return;
	}

	Matrix operator*(Matrix other) const {
		Matrix res;
		for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) for (int k = 1; k <= n; k++) res.a[i][j] = (res.a[i][j] + a[i][k] * other.a[k][j] % mod) % mod;
		return res;
	}
};

Matrix A;

int main() {
	scanf("%lld%lld", &n, &k);
	for (int i =1 ; i <= n; i++) for (int j = 1; j <= n; j++) scanf("%lld", &A.a[i][j]);
	Matrix ans;
	for (int i = 1; i <= n; i++) ans.a[i][i] = 1;
	while (k) {
		if (k & 1){
			ans = ans * A;
		}
		k >>= 1;
		A = A * A;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) printf("%lld ", ans.a[i][j]);
		printf("\n");
	}
	return 0;
}