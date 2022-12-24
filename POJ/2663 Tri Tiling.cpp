#include <cstdio>
#include <cstring>

const int maxN = 5;
const int maxM = 5;

struct Matrix {
    int n, m;
    int a[maxN][maxM];

    void clear() {
        n = 0;
        m = 0;
        std::memset(a, 0, sizeof(a));
        return;
    }

    Matrix operator*(const Matrix &other) const {
        Matrix ret;
        ret.clear();
        ret.n = n;
        ret.m = other.m;
        for (int i = 1; i <= n; i++) 
            for (int j = 1; j <= other.m; j++)
                for (int k = 1; k <= m; k++)
                    ret.a[i][j] += a[i][k] * other.a[k][j];
        return ret;
    }
};

Matrix pow(Matrix A, int p) {
	Matrix ret;
	ret.clear();
	ret.n = A.n;
	ret.m = A.n;
	for (int i = 1; i <= A.n; i++) ret.a[i][i] = 1;
	while (p) {
		if (p & 1) ret = A * ret;
		A = A * A;
		p >>= 1;
	}
	return ret;
}

int n;

void mian() {
	if (n == 0) {
		printf("%d\n", 1);
		return;
	}

	if (n % 2) {
		printf("%d\n", 0);
		return;
	}

	Matrix A;
	A.clear();
	A.n = 4;
	A.m = 1;
	A.a[1][1] = 11;
	A.a[3][1] = 3;

	if (n < 4) {
		printf("%d\n", A.a[4 - n + 1][1]);
		return;
	}

	Matrix T;
	T.clear();
	T.n = 4;
	T.m = 4;
	T.a[1][2] = 4;
	T.a[1][4] = -1;
	T.a[2][1] = 1;
	T.a[3][2] = 1;
	T.a[4][3] = 1;

	printf("%d\n", (pow(T, n - 4) * A).a[1][1]);
	return;
}

int main() {
	while (scanf("%d", &n) && n != -1) mian();
	return 0;
}