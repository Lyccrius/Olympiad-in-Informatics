//2000000016
//329616

#include <iostream>

int t;
int n;
int m;

int read() {
    int ret = 0;
    int sym = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') sym = - sym;
        ch = getchar();
    }
    while (isdigit(ch)) {
        ret = (1ll * ret * 10 + ch - '0') % 329616;
        ch = getchar();
    }
    return ret;
}

struct Matrix {
    int n;
    int m;
    int a[5][5];
    int mod;

    Matrix operator*(const Matrix &other) {
        Matrix ret;
        ret.n = this->n;
        ret.m = other.m;
        ret.mod = mod;
        for (int i = 1; i <= ret.n; i++) {
            for (int j = 1; j <= ret.m; j++) {
                ret.a[i][j] = 0;
                for (int k = 1; k <= other.n; k++) {
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

Matrix pow(Matrix a, int b, int mod) {
    Matrix ret = I;
    ret.mod = mod;
    a.mod = mod;
    while (b) {
        //printf("b = %d\n", b);
        if (b & 1) ret = ret * a;
        a = a * a;
        b = b / 2;
        //printf("ret:\n"); ret.show();
        //printf("a:\n"); a.show();
    }
    return ret;
}

int F(int n, int mod) {
    I.n = I.m = 2;
    I.a[1][1] = I.a[2][2] = 1;
    A.n = 2;
    A.m = 1;
    A.a[1][1] = A.a[2][1] = 1;
    T.n = T.m = 2;
    T.a[1][1] = 0;
    T.a[1][2] = 1;
    T.a[2][1] = T.a[2][2] = 1;
    if (n == 0) return 0;
    if (n <= 2) return 1;
    A = pow(T, n - 2, mod) * A;
    return A.a[2][1];
}

void mian() {
    n = read();
    //printf("n = %d\n", n);
    m = F(n, 2000000016);
    //printf("m = %d\n", m);
    std::cout << F(m, 1000000007) << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}