#include <iostream>

typedef double dbl;

const int maxN = 100;

int r, s, p;
dbl R, S, P;
dbl f[maxN + 10][maxN + 10][maxN + 10];

int main() {
    std::cin >> r >> s >> p;
    f[r][s][p] = 1;
    for (int i = r; i >= 0; i--) {
        for (int j = s; j >= 0; j--) {
            for (int k = p; k >= 0; k--) {
                dbl t = i * j + j * k + k * i;
                if (!t) continue;
                if (i) f[i - 1][j][k] += f[i][j][k] * k * i / t;
                if (j) f[i][j - 1][k] += f[i][j][k] * i * j / t;
                if (k) f[i][j][k - 1] += f[i][j][k] * j * k / t;
            }
        }
    }
    for (int i = 1; i <= r; i++) R += f[i][0][0];
    for (int j = 1; j <= s; j++) S += f[0][j][0];
    for (int k = 1; k <= p; k++) P += f[0][0][k];
    printf("%.12lf %.12lf %.12lf", R, S, P);
    return 0;
}