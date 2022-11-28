#include <cstdio>
#include <cstring>

const int mod = 1e9 + 7;

int T;
int n;

struct Matrix {
	long long a[5][5];

	Matrix() {
		std::memset(a, 0, sizeof(a));
		return;
	}

	Matrix operator*(Matrix other) const {
		Matrix res;
		for (int i = 1; i <= 3; i++) for (int j = 1; j <= 3; j++) for (int k = 1; k <= 3; k++) res.a[i][j] = (res.a[i][j] + a[i][k] * other.a[k][j] % mod) % mod;
		return res;
	}
};

void mian() {
	scanf("%d", &n);
	Matrix a;
	Matrix ans;
	a.a[1][1] = 1; a.a[1][2] = 0; a.a[1][3] = 1;
	a.a[2][1] = 1; a.a[2][2] = 0; a.a[2][3] = 0;
	a.a[3][1] = 0; a.a[3][2] = 1; a.a[3][3] = 0;
	for (int i = 1; i <= 3; i++) ans.a[i][i] = 1;
	while (n) {
		if (n & 1){
			ans = ans * a;
		}
		n >>= 1;
		a = a * a;
	}
	printf("%lld\n", ans.a[2][1]);
}

int main() {
	scanf("%d", &T);
	while (T--) mian();
	return 0;
}