#include <iostream>
#include <algorithm>
#include <vector>

typedef std::vector<int> vic;

const int maxN = 1e6;
const int maxT = 100;
const int inf = 1e9 + 10;

int n, t, s, e;
int w[maxT + 10], u[maxT + 10], v[maxT + 10];
vic raw;

struct Matrix {
    int n, m;
    int a[2 * maxT + 10][2 * maxT + 10];

    Matrix() {
        n = 2 * maxT;
        m = 2 * maxT;
        std::fill(a[0], a[0] + sizeof(a) / 8, inf);
        return;
    }

    Matrix operator*(const Matrix &other) const {
        Matrix ret;
        ret.n = n;
        ret.m = other.m;
        for (int i = 1; i <= ret.n; i++) {
            for (int j = 1; j <= ret.m; j++) {
                for (int k = 1; k <= m; k++) {
                    ret.a[i][j] = std::min(ret.a[i][j], a[i][k] + other.a[k][j]);
                }
            }
        }
        return ret;
    }
} A;

Matrix pow(Matrix a, int b) {
    Matrix ret = A;
    while (b) {
        if (b & 1) ret = ret * a;
        a = a * a;
        b = b / 2;
    }
    return ret;
}

int main() {
    std::cin >> n >> t >> s >> e;
    for (int i = 1; i <= t; i++) {
        std::cin >> w[i] >> u[i] >> v[i];
        raw.push_back(u[i]);
        raw.push_back(v[i]);
    }
    std::sort(raw.begin(), raw.end());
    raw.erase(std::unique(raw.begin(), raw.end()), raw.end());
    s = std::lower_bound(raw.begin(), raw.end(), s) - raw.begin() + 1;
    e = std::lower_bound(raw.begin(), raw.end(), e) - raw.begin() + 1;
    for (int i = 1; i <= t; i++) {
        u[i] = std::lower_bound(raw.begin(), raw.end(), u[i]) - raw.begin() + 1;
        v[i] = std::lower_bound(raw.begin(), raw.end(), v[i]) - raw.begin() + 1;
        A.a[u[i]][v[i]] = w[i];
        A.a[v[i]][u[i]] = w[i];
    }
    std::cout << pow(A, n - 1).a[s][e] << '\n';
    return 0;
}