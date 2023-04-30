#include <iostream>

typedef long long lxl;
typedef char chr;

const int maxM = 100000;
const int mod = 1e9 + 7;

lxl n;
int a[30][30];
chr s1[maxM + 10];
int ans;

struct Matrix {
    int n;
    int m;
    int a[30][30];

    Matrix operator*(const Matrix &other) {
        Matrix ret;
        ret.n = this->n;
        ret.m = other.m;
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
        return;
    }
} I, A, T;

Matrix pow(Matrix a, lxl b) {
    Matrix ret = I;
    while (b) {
        if (b & 1) ret = ret * a;
        a = a * a;
        b = b / 2;
    }
    return ret;
}

int main() {
    I.n = I.m = 26;
    for (int i = 1; i <= 26; i++) I.a[i][i] = 1;
    A.n = 26;
    A.m = 1;
    for (int i = 1; i <= 26; i++) A.a[i][1] = 1;
    T.n = 26;
    T.m = 26;
    for (int i = 1; i <= 26; i++) for (int j = 1; j <= 26; j++) T.a[i][j] = 1;
    std::cin >> n;
    std::cin >> (s1 + 1);
    for (int i = 2; s1[i]; i++) {
        int u = s1[i - 1] - 'a' + 1;
        int v = s1[i] - 'a' + 1;
        T.a[u][v] = 0;
    }
    A = pow(T, n - 1) * A;
    for (int i = 1; i <= 26; i++) ans = (ans + A.a[i][1]) % mod;
    std::cout << ans << '\n';
    return 0;
}