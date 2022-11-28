#include <cstdio>
#include <cstring>

const int mod = 1e9 + 7;

long long n;

struct Matrix {
	long long a[5][5];

	Matrix() {
		std::memset(a, 0, sizeof(a));
		return;
	}

	Matrix operator*(Matrix other) const {
		Matrix res;
		for (int i = 1; i <= 2; i++) for (int j = 1; j <= 2; j++) for (int k = 1; k <= 2; k++) res.a[i][j] = (res.a[i][j] + a[i][k] * other.a[k][j]) % mod;
		return res;
	}
};

int main() {
	scanf("%lld", &n);
	Matrix a;
	Matrix ans;
	a.a[1][1] = 1; a.a[1][2] = 1;
	a.a[2][1] = 1; a.a[2][2] = 0;
	for (int i = 1; i <= 2; i++) ans.a[i][i] = 1;
	while (n) {
		if (n & 1){
			ans = ans * a;
		}
		n >>= 1;
		a = a * a;
	}
	printf("%lld\n", ans.a[2][1]);
	return 0;
}