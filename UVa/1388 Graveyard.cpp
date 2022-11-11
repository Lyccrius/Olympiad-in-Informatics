#include <cstdio>
#include <cmath>

int n, m;

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        double ans = 0.0;
        for (int i = 1; i < n; i++) {
            double pos = (double)i / n * (n + m);
            ans += std::fabs(pos - floor(pos + 0.5)) / (n + m);
        }
        printf("%.4lf\n", ans * 10000);
    }
    return 0;
}