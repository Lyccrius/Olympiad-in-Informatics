#include <cstdio>
#include <cmath>

const double eps = 1e-6;

double n, m, k;

bool check(double x) {
	return std::pow(1.0 / (1.0 + x), k) >= 1 - n / m * x;
}

int main() {
	scanf("%lf%lf%lf", &n, &m, &k);
    double l = 0;
    double r = 10;
	while (r - l >= eps) {
		double mid = (l + r) / 2;
		if (check(mid)) r = mid;
		else l = mid;
	}
	printf("%.1lf\n", l * 100);
	return 0;
} 