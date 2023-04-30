#include <iostream>
#include <set>

typedef long long lxl;
typedef std::set<int> sit;

const int maxX = 100;
const int mod = 1e9 + 7;

lxl n;
int PR;
sit pr;
int NF;
sit nf;
int x;
sit xs;

struct Matrix {
    int n;
    int m;
    int a[maxX + 10][maxX + 10];

    Matrix operator*(const Matrix &other) {
        Matrix ret;
        ret.n = this->n;
        ret.m = other.m;
        for (int i = 0; i <= ret.n; i++) {
            for (int j = 0; j <= ret.m; j++) {
                ret.a[i][j] = 0;
                for (int k = 0; k <= other.n; k++) {
                    ret.a[i][j] = (ret.a[i][j] + 1ll * a[i][k] * other.a[k][j] % mod) % mod;
                }
            }
        }
        return ret;
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
    std::cin >> n;
    std::cin >> PR;
    for (int i = 1; i <= PR; i++) std::cin >> x, pr.insert(x);
    std::cin >> NF;
    for (int i = 1; i <= NF; i++) std::cin >> x, nf.insert(x);
    for (auto x : pr) if (nf.count(x)) xs.insert(x);
    I.n = I.m = 100;
    for (int i = 1; i <= 100; i++) I.a[i][i] = 1;
    A.n = 100;
    A.m = 1;
    A.a[0][1] = 1;
    for (int i = 1; i <= 100; i++) {
        for (auto x : xs) {
            if (i >= x) {
                A.a[i][1] = (A.a[i][1] + A.a[i - x][1]) % mod;
            }
        }
    }
    T.n = T.m = 100;
    for (auto x : xs) T.a[100][100 - x + 1] = 1;
    for (int i = 1; i < 100; i++) T.a[i][i + 1] = 1;
    if (n <= 100) {
        std::cout << A.a[n][1] << '\n';
        return 0;
    }
    A = pow(T, n - 100) * A;
    std::cout << A.a[100][1] << '\n';
}