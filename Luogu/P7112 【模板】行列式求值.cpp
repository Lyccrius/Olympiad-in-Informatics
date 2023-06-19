#include <iostream>

const int maxN = 600;
const int maxP = 1e9 + 7;

int n, p;

struct Matrix {
    int n;
    int a[maxN + 10][maxN + 10];

    void scan(int n) {
        this->n = n;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                std::cin >> a[i][j];
            }
        }
        return;
    }

    int vert() {
        int ret = 1;
        int sym = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                while (a[i][i]) {
                    int x = a[j][i] / a[i][i];
                    for (int k = i; k <= n; k++) {
                        a[j][k] = (a[j][k] - 1ll * x * a[i][k] % p + p) % p;
                    }
                    std::swap(a[i], a[j]);
                    sym = - sym;
                }
                std::swap(a[i], a[j]);
                sym = - sym;
            }
        }
        for (int i = 1; i <= n; i++) ret = 1ll * ret * a[i][i] % p;
        return (sym * ret % p + p) % p;
    }
} A;

int main() {
    std::cin >> n >> p;
    A.scan(n);
    std::cout << A.vert() << '\n';
    return 0;
}