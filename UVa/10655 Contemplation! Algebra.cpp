#include <iostream>

typedef long long lxl;

lxl p, q, n;

struct Matrix {
	int n, m;
	lxl a[5][5];

	Matrix() {
		std::fill(a[0], a[0] + sizeof(a) / 8, 0);
		return;
	}

	Matrix operator*(const Matrix &other) {
		Matrix ret;
		ret.n = n;
		ret.m = other.m;
		for (int i = 1; i <= ret.n; i++) {
			for (int j = 1; j <= ret.m; j++) {
				for (int k = 1; k <= m; k++) {
					ret.a[i][j] += a[i][k] * other.a[k][j];
				}
			}
		}
		return ret;
	}
} A, T;

Matrix pow(Matrix a, lxl b) {
	Matrix ret;
	ret.n = a.n;
	ret.m = a.m;
	for (int i = 1; i <= ret.n; i++) ret.a[i][i] = 1;
	while (b) {
		if (b & 1) ret = ret * a;
		a = a * a;
		b = b / 2;
	}
	return ret;
}

void mian() {
	A.n = 1;
	A.m = 2;
	A.a[1][1] = p;
	A.a[1][2] = 2;
	T.n = 2;
	T.m = 2;
	T.a[1][1] = p;
	T.a[1][2] = 1;
	T.a[2][1] = -q;
	T.a[2][2] = 0;
	std::cout << (A * pow(T, n)).a[1][2] << '\n';
	return;
}

int main() {
	while (scanf("%lld%lld%lld", &p, &q, &n) == 3) mian();
	return 0;
}