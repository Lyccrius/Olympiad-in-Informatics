#include <iostream>

int p, q, a1, a2, n, m;
int mod;

struct Matrix {
    int n;
    int m;
    int a[100][100];

    Matrix operator*(const Matrix &other) {
        Matrix ret;
        ret.n = n;
        ret.m = other.m;
        for (int i = 1; i <= ret.n; i++) {
            for (int j = 1; j <= ret.m; j++) {
                ret.a[i][j] = 0;
                for (int k = 1; k <= m; k++) {
                    ret.a[i][j] = (ret.a[i][j] + 1ll * a[i][k] * other.a[k][j] % mod) % mod;
                }
            }
        }
        return ret;
    }

    void show() {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                std::cout << a[i][j] << ' ';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
        return;
    }
} I, A, T;

Matrix pow(Matrix a, int b) {
    Matrix ret = I;
    while (b) {
        if (b & 1) ret = a * ret;
        a = a * a;
        b = b / 2;
    }
    return ret;
}

int main() {
    std::cin >> p >> q >> a1 >> a2 >> n >> m;
    mod = m;
    a1 %= mod;
    a2 %= mod;
    if (n == 1) {
        std::cout << a1 << '\n';
        return 0;
    }
    if (n == 2) {
        std::cout << a2 << '\n';
        return 0;
    }
    I.n = I.m = 2;
    I.a[1][1] = I.a[2][2] = 1;
    A.n = 2;
    A.m = 1;
    A.a[1][1] = a2;
    A.a[2][1] = a1;
    T.n = T.m = 2;
    T.a[1][1] = p;
    T.a[1][2] = q;
    T.a[2][1] = 1;
    A = pow(T, n - 2) * A;
    //A.show();
    std::cout << A.a[1][1] << '\n';
    return 0;
}