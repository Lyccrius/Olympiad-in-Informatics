#include <iostream>
#include <algorithm>
#include <vector>

typedef std::pair<int, int> pii;

const int maxN = 30;
const int maxM = 30;
const double eps = 1e-6;

int kase;
int n, m;
double a[maxN + 10][maxM + 10];
double t;

bool check(double x) {
    double ret = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] < x) {
                ret += (x - a[i][j]) * 100;
            } 
        }
    }
    //printf("check(%.2lf) = %.2lf\n", x, ret);
    return ret >= t;
}

double solve(double x) {
    double ret = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] < x) {
                ret += 1;
            }
        }
    }
    return ret * 100 / n / m;
}

void mian() {
    double maxA = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            std::cin >> a[i][j];
            maxA = std::max(maxA, a[i][j]);
        }
    }
    std::cin >> t;
    double l = -1e9;
    double r = 1e9;
    while (r - l >= eps) {
        double mid = (l + r) / 2;
        if (check(mid)) r = mid;
        else l = mid;
    }
    //if (kase) printf("\n");
    printf("Region %d\n", ++kase);
    printf("Water level is %.2lf meters.\n", l);
    printf("%.2lf percent of the region is under water.\n", solve(l));
    printf("\n");
    return;
}

int main() {
    while (std::cin >> n >> m && n && m) mian();
    return 0;
}