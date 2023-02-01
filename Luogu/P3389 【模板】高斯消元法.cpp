#include <iostream>
#include <cmath>

const int maxN = 100;
const double eps = 1e-6;

int n;
int cur = 1;

struct Matrix {
    double a[maxN + 10][maxN + 10];

    void show() {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) printf("%.2lf ", a[i][j]);
            printf("\n");
        }
        return;
    }
} mat;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n + 1; j++) std::cin >> mat.a[i][j];
    for (int j = 1; j <= n; j++) {
        int t;
        //printf("###considering column %d### cur = %d\n", j, cur);
        for (t = cur; t <= n; t++) if (std::fabs(mat.a[t][j]) > eps) break;
        if (t > n) continue;
        //printf("found non-0 at row %d\n", t);
        //mat.show();
        for (int k = j; k <= n + 1; k++) std::swap(mat.a[t][k], mat.a[cur][k]);
        //printf("swaped row %d and row %d\n", t, j);
        //mat.show();
        for (int k = n + 1; k >= j; k--) mat.a[cur][k] /= mat.a[cur][j];
        //printf("turn row %d to 1\n", cur);
        //mat.show();
        for (int i = 1; i <= n; i++) if (i != cur) for (int k = n + 1; k >= j; k--) mat.a[i][k] -= mat.a[cur][k] * mat.a[i][j];
        //printf("approxed\n");
        //mat.show();
        cur++;
    }
    if (cur <= n) {
        printf("No Solution");
    } else {
        for (int i = 1; i <= n; i++) printf("%.2lf\n", i, mat.a[i][n + 1]);
    }
    return 0;
}