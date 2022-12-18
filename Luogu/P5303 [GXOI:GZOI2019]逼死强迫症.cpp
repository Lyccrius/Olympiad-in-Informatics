#include<cstdio>
#include<cstring>

const int mod = 1e9 + 7;

struct Matrix {
    int a[5][5];

	Matrix () {
		std::memset(a, 0, sizeof(a));
		return;
	}
	
    Matrix operator*(Matrix b) const {
        Matrix c;
        for (int i = 0; i < 5; i++) for (int k = 0; k < 5; k++) for (int j = 0; j < 5; j++) c.a[i][j] = (c.a[i][j] + (long long)a[i][k] * b.a[k][j]) % mod;
        return c;
    }
} s;

Matrix pow(Matrix a, int b) {
    Matrix ret;
    ret.a[0][0] = 1;
	ret.a[1][1] = 1;
	ret.a[2][2] = 1;
	ret.a[3][3] = 1;
	ret.a[4][4] = 1;
	while (b) {
		if (b & 1) ret = ret * a;
		a = a * a;
		b >>= 1;
	}
    return ret;
}

int main() {
    s.a[0][1] = 1;
	s.a[1][0] = 1;
	s.a[1][1] = 1;
	s.a[2][3] = 1;
	s.a[3][2] = 1;
	s.a[3][3] = 1;
	s.a[4][4] = 1;
    s.a[3][1] = 2;
	s.a[4][1] = mod - 1;
    int T;
	scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        if (n < 3) printf("%d\n", 0);
        else {
            Matrix ans;
            ans.a[0][2] = 1;
			ans.a[0][3] = 2;
			ans.a[0][4] = 2;
            printf("%d\n",(ans * pow(s, n - 2)).a[0][1]);
        }
    }
    return 0;
}